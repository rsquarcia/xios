#include "shared_boundary.hpp"

#include <algorithm>
#include <climits>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sphereRemap {
namespace {

const double LON_TOL = 1.e-12;
const double PI = 3.141592653589793238462643383279502884;
const double TWO_PI = 2.0 * PI;

/** Orthonormal frame attached to the grid pole.

    `pole` is kept verbatim: the eligibility predicate and the small-circle key
    below must be evaluated with exactly the vector normals() and
    createGreatCirclePolygon() use, not with a renormalised copy of it.
    `axis` is the unit pole and is used for the metric parts (azimuth, and moving
    a point onto a small circle).

    For pole = (0,0,1) this yields axis = (0,0,1), e1 = (1,0,0), e2 = (0,1,0)
    exactly, so azimuth() below is bit-for-bit atan2(y, x). */
struct PoleFrame
{
  Coord pole;
  Coord axis;
  Coord e1;
  Coord e2;
};

PoleFrame makePoleFrame(const Coord& pole)
{
  PoleFrame frame;
  frame.pole = pole;
  frame.axis = proj(pole);
  // reference direction: the coordinate axis least aligned with the pole, lowest index winning ties
  const double ax = std::fabs(frame.axis.x);
  const double ay = std::fabs(frame.axis.y);
  const double az = std::fabs(frame.axis.z);
  Coord reference(1.0, 0.0, 0.0);
  if (ay < ax && ay <= az) reference = Coord(0.0, 1.0, 0.0);
  else if (az < ax && az < ay) reference = Coord(0.0, 0.0, 1.0);
  frame.e2 = proj(crossprod(frame.axis, reference));
  frame.e1 = crossprod(frame.e2, frame.axis);
  return frame;
}

/** Angle of `coord` about the pole, in [0, 2 pi). */
double azimuth(const PoleFrame& frame, const Coord& coord)
{
  double angle = std::atan2(scalarprod(coord, frame.e2), scalarprod(coord, frame.e1));
  if (angle < 0.0) angle += TWO_PI;
  return angle;
}

/** Signed distance from the origin to the plane of the small circle through
    `coord`, measured along the pole. This is exactly the quantity normals()
    stores in Elt::d for a small-circle edge (elt.hpp), and the quantity
    createGreatCirclePolygon() rebuilds the arc from (intersection_ym.cpp).
    Elt::d is taken from the FIRST vertex of an edge, and the two owners of a
    shared boundary traverse it in opposite directions, so they describe the same
    circle only if they agree on this value bit for bit. */
double latitudeKey(const PoleFrame& frame, const Coord& coord)
{
  return scalarprod(coord, frame.pole);
}

/** Exactly the negation of the great-circle branch of normals() (elt.hpp):

      great circle  <=>  pole == ORIGIN || fabs(scalarprod(t, pole)) > EPS

    with t = vertex[j] - vertex[i]. Using the same expression, the same operand
    order and the same EPS makes the registry and the classifier it serves agree
    by construction rather than by coincidence. */
bool isSmallCircleEdge(const PoleFrame& frame, const Coord& a, const Coord& b)
{
  if (frame.pole == ORIGIN) return false;
  return std::fabs(scalarprod(b-a, frame.pole)) <= EPS;
}

/** Move `coord` onto the small circle whose pole distance is exactly
    `targetKey`, keeping its azimuth. `coordKey` is latitudeKey(frame, coord).

    For pole = (0,0,1) the result is (x*s, y*s, targetKey) with the third
    component bit-for-bit `targetKey`, so latitudeKey() of the result is exactly
    `targetKey` and both owners of the boundary get the identical Elt::d.

    A point that already lies on the canonical circle is returned untouched, so
    on a mesh whose two owners already agree exactly -- the normal case -- this
    routine never perturbs a coordinate. */
Coord rebase(const PoleFrame& frame, const Coord& coord, double coordKey, double targetKey)
{
  if (coordKey == targetKey) return coord;
  const Coord centre = frame.axis*targetKey;
  const Coord perpendicular = coord - frame.axis*coordKey;
  const double radius = norm(perpendicular);
  const double targetRadiusSquared = 1.0 - targetKey*targetKey;
  if (radius <= 0.0 || targetRadiusSquared <= 0.0) return centre;
  return centre + perpendicular*(std::sqrt(targetRadiusSquared)/radius);
}

struct BoundaryPoint
{
  Coord coord;
  double lon;
};

struct LatitudeBreakpoints
{
  double keyLat;                       /**< canonical pole distance, taken verbatim from one actual input coordinate */
  std::vector<BoundaryPoint> points;   /**< canonical breakpoints, all exactly on keyLat */
};

struct Registry
{
  std::vector<LatitudeBreakpoints> latitudes;
  /** Every distinct input key, paired with the latitude it was grouped into, so
      that lookup is an exact match and never re-applies the tolerance. */
  std::vector<std::pair<double, size_t> > lookup;
};

bool coordLess(const Coord& lhs, const Coord& rhs)
{
  if (lhs.z != rhs.z) return lhs.z < rhs.z;
  if (lhs.x != rhs.x) return lhs.x < rhs.x;
  return lhs.y < rhs.y;
}

double longitudeDelta(const PoleFrame& frame, const Coord& from, const Coord& to)
{
  double delta = azimuth(frame, to) - azimuth(frame, from);
  if (delta > PI) delta -= TWO_PI;
  else if (delta <= -PI) delta += TWO_PI;
  return delta;
}

/** An edge spanning half a turn or more about the pole has no well-defined
    azimuthal direction -- longitudeDelta() folds into (-pi, pi] -- so the arc
    between its endpoints is ambiguous and breakpoints cannot be ordered along it.
    XIOS meshes do not contain such cells; this is a guard, not a supported case. */
bool longitudeSpanIsInvalid(const PoleFrame& frame, const Coord& a, const Coord& b)
{
  return squaredist(a, b) > EPS*EPS && std::fabs(longitudeDelta(frame, a, b)) >= PI-LON_TOL;
}

void collectLatitudeEndpoints(const PoleFrame& frame, const Coord* vertices, int count,
                              std::vector<Coord>& endpoints, bool& invalidSpan)
{
  for (int i = 0; i < count; ++i)
  {
    const Coord& a = vertices[i];
    const Coord& b = vertices[(i+1)%count];
    if (isSmallCircleEdge(frame, a, b))
    {
      if (longitudeSpanIsInvalid(frame, a, b)) invalidSpan = true;
      endpoints.push_back(a);
      endpoints.push_back(b);
    }
  }
}

void collectLatitudeEndpoints(const PoleFrame& frame, const Elt& element,
                              std::vector<Coord>& endpoints, bool& invalidSpan)
{
  collectLatitudeEndpoints(frame, element.vertex.data(), element.n, endpoints, invalidSpan);
}

std::vector<Coord> collectLocalEndpoints(
    const PoleFrame& frame,
    const std::vector<Elt>& elements,
    const double* fullBoundsLon,
    const double* fullBoundsLat,
    int nVertex,
    int fullNbCells,
    bool& invalidSpan)
{
  std::vector<Coord> endpoints;
  if (fullBoundsLon != nullptr && fullBoundsLat != nullptr && nVertex > 0 && fullNbCells > 0)
  {
    endpoints.reserve(2*static_cast<size_t>(nVertex)*fullNbCells);
    for (int i = 0; i < fullNbCells; ++i)
    {
      const double* boundsLon = fullBoundsLon+i*nVertex;
      const double* boundsLat = fullBoundsLat+i*nVertex;
      std::vector<Coord> vertices(nVertex);
      int count = 0;
      vertices[count++] = xyz(boundsLon[0], boundsLat[0]);
      for (int vertex = 1; vertex < nVertex; ++vertex)
      {
        vertices[count] = xyz(boundsLon[vertex], boundsLat[vertex]);
        if (count >= 3 && squaredist(vertices[count], vertices[0]) < EPS*EPS) break;
        if (squaredist(vertices[count], vertices[count-1]) > EPS*EPS) ++count;
      }
      collectLatitudeEndpoints(frame, vertices.data(), count, endpoints, invalidSpan);
    }
  }
  else
  {
    for (std::vector<Elt>::const_iterator it = elements.begin(); it != elements.end(); ++it)
      collectLatitudeEndpoints(frame, *it, endpoints, invalidSpan);
  }

  std::sort(endpoints.begin(), endpoints.end(), coordLess);
  endpoints.erase(std::unique(endpoints.begin(), endpoints.end()), endpoints.end());
  return endpoints;
}

std::vector<Coord> exchangeEndpoints(const std::vector<Coord>& local, MPI_Comm communicator)
{
  int mpiSize;
  MPI_Comm_size(communicator, &mpiSize);

  const unsigned long long localCount = local.size() > static_cast<size_t>(INT_MAX/3)
                                           ? static_cast<unsigned long long>(INT_MAX)+1ULL
                                           : 3ULL*static_cast<unsigned long long>(local.size());
  std::vector<unsigned long long> wideCounts(mpiSize);
  MPI_Allgather(&localCount, 1, MPI_UNSIGNED_LONG_LONG,
                wideCounts.data(), 1, MPI_UNSIGNED_LONG_LONG, communicator);

  std::vector<int> counts(mpiSize);
  std::vector<int> displacements(mpiSize);
  unsigned long long total = 0;
  for (int rank = 0; rank < mpiSize; ++rank)
  {
    if (wideCounts[rank] > static_cast<unsigned long long>(INT_MAX) ||
        total > static_cast<unsigned long long>(INT_MAX) ||
        wideCounts[rank] > static_cast<unsigned long long>(INT_MAX)-total)
      throw std::runtime_error("conformSharedLatitudeBoundaries: MPI count or displacement exceeds INT_MAX");
    counts[rank] = static_cast<int>(wideCounts[rank]);
    displacements[rank] = static_cast<int>(total);
    total += wideCounts[rank];
  }

  std::vector<double> send(static_cast<size_t>(localCount));
  for (size_t i = 0; i < local.size(); ++i)
  {
    send[3*i] = local[i].x;
    send[3*i+1] = local[i].y;
    send[3*i+2] = local[i].z;
  }

  std::vector<double> receive(static_cast<size_t>(total));
  MPI_Allgatherv(send.data(), static_cast<int>(localCount), MPI_DOUBLE,
                 receive.data(), counts.data(), displacements.data(), MPI_DOUBLE, communicator);

  std::vector<Coord> global(receive.size()/3);
  for (size_t i = 0; i < global.size(); ++i)
    global[i] = Coord(receive[3*i], receive[3*i+1], receive[3*i+2]);
  return global;
}

Registry buildRegistry(const PoleFrame& frame, const std::vector<Coord>& coordinates)
{
  struct KeyedPoint
  {
    Coord coord;
    double key;
    double lon;
  };

  std::vector<KeyedPoint> sorted;
  sorted.reserve(coordinates.size());
  for (size_t i = 0; i < coordinates.size(); ++i)
  {
    KeyedPoint point;
    point.coord = coordinates[i];
    point.key = latitudeKey(frame, coordinates[i]);
    point.lon = azimuth(frame, coordinates[i]);
    sorted.push_back(point);
  }

  // Exact strict ordering only. The tolerance is applied afterwards, in a single
  // linear pass, and never inside a comparator.
  std::sort(sorted.begin(), sorted.end(), [](const KeyedPoint& lhs, const KeyedPoint& rhs)
  {
    if (lhs.key != rhs.key) return lhs.key < rhs.key;
    if (lhs.lon != rhs.lon) return lhs.lon < rhs.lon;
    return coordLess(lhs.coord, rhs.coord);
  });

  Registry registry;
  for (size_t latBegin = 0; latBegin < sorted.size(); )
  {
    // Leader-based bucket: every member is compared with the one fixed leader, so
    // a bucket can never span more than EPS however many points it contains.
    // Keys are ascending, so the difference below is non-negative by construction.
    size_t latEnd = latBegin+1;
    while (latEnd < sorted.size() && sorted[latEnd].key-sorted[latBegin].key <= EPS)
      ++latEnd;

    // The canonical small circle is defined by one actual input coordinate -- the
    // bucket leader -- and its key is taken from that coordinate. No key is ever
    // averaged over the bucket.
    const Coord canonical = sorted[latBegin].coord;
    const double keyLat = latitudeKey(frame, canonical);

    std::vector<BoundaryPoint> latitudePoints;
    latitudePoints.reserve(latEnd-latBegin);
    for (size_t i = latBegin; i < latEnd; ++i)
      latitudePoints.push_back(BoundaryPoint{sorted[i].coord, sorted[i].lon});
    std::sort(latitudePoints.begin(), latitudePoints.end(), [](const BoundaryPoint& lhs, const BoundaryPoint& rhs)
    {
      if (lhs.lon != rhs.lon) return lhs.lon < rhs.lon;
      return coordLess(lhs.coord, rhs.coord);
    });

    struct PointGroup
    {
      double minLon;
      double maxLon;
      Coord representative;
    };
    std::vector<PointGroup> groups;
    for (size_t lonBegin = 0; lonBegin < latitudePoints.size(); )
    {
      size_t lonEnd = lonBegin+1;
      Coord representative = latitudePoints[lonBegin].coord;
      while (lonEnd < latitudePoints.size() && latitudePoints[lonEnd].lon-latitudePoints[lonBegin].lon <= LON_TOL)
      {
        if (coordLess(latitudePoints[lonEnd].coord, representative))
          representative = latitudePoints[lonEnd].coord;
        ++lonEnd;
      }
      groups.push_back(PointGroup{latitudePoints[lonBegin].lon,
                                  latitudePoints[lonEnd-1].lon,
                                  representative});
      lonBegin = lonEnd;
    }

    if (groups.size() > 1 && groups.front().maxLon+TWO_PI-groups.back().minLon <= LON_TOL)
    {
      if (coordLess(groups.back().representative, groups.front().representative))
        groups.front().representative = groups.back().representative;
      groups.pop_back();
    }

    LatitudeBreakpoints latitude;
    latitude.keyLat = keyLat;
    latitude.points.reserve(groups.size());
    for (size_t i = 0; i < groups.size(); ++i)
    {
      // Each group representative is an actual input coordinate; it is moved onto
      // the canonical small circle so that every breakpoint of this latitude has
      // the identical pole distance.
      const Coord snapped = rebase(frame, groups[i].representative,
                                   latitudeKey(frame, groups[i].representative), keyLat);
      latitude.points.push_back(BoundaryPoint{snapped, azimuth(frame, snapped)});
    }
    std::sort(latitude.points.begin(), latitude.points.end(), [](const BoundaryPoint& lhs, const BoundaryPoint& rhs)
    {
      if (lhs.lon != rhs.lon) return lhs.lon < rhs.lon;
      return coordLess(lhs.coord, rhs.coord);
    });

    const size_t latitudeIndex = registry.latitudes.size();
    registry.latitudes.push_back(latitude);
    for (size_t i = latBegin; i < latEnd; ++i)
      if (registry.lookup.empty() || registry.lookup.back().first != sorted[i].key)
        registry.lookup.push_back(std::make_pair(sorted[i].key, latitudeIndex));

    latBegin = latEnd;
  }
  return registry;
}

/** Exact lookup. Every key an element can present was gathered into the registry,
    so the tolerance is applied once at construction and never again here; two
    owners can therefore never resolve the same boundary to different latitudes. */
const LatitudeBreakpoints* findLatitude(const Registry& registry, double key)
{
  std::vector<std::pair<double, size_t> >::const_iterator it =
      std::lower_bound(registry.lookup.begin(), registry.lookup.end(), key,
                       [](const std::pair<double, size_t>& entry, double value)
                       { return entry.first < value; });
  if (it != registry.lookup.end() && it->first == key) return &registry.latitudes[it->second];
  return nullptr;
}

double cyclicDistance(double a, double b)
{
  double distance = std::fabs(a-b);
  return std::min(distance, TWO_PI-distance);
}

Coord snap(const PoleFrame& frame, const LatitudeBreakpoints& latitude, const Coord& coord)
{
  const double lon = azimuth(frame, coord);
  std::vector<BoundaryPoint>::const_iterator it =
      std::lower_bound(latitude.points.begin(), latitude.points.end(), lon,
                       [](const BoundaryPoint& point, double value)
                       { return point.lon < value; });

  const BoundaryPoint* best = nullptr;
  double bestDistance = LON_TOL;
  for (int offset = -1; offset <= 1; ++offset)
  {
    if (latitude.points.empty()) break;
    long index = static_cast<long>(it-latitude.points.begin())+offset;
    while (index < 0) index += latitude.points.size();
    while (index >= static_cast<long>(latitude.points.size())) index -= latitude.points.size();
    const BoundaryPoint& point = latitude.points[index];
    const double distance = cyclicDistance(lon, point.lon);
    if (distance <= bestDistance &&
        (best == nullptr || distance < bestDistance || coordLess(point.coord, best->coord)))
    {
      best = &point;
      bestDistance = distance;
    }
  }
  // Fall back on the canonical latitude even when no breakpoint is close enough,
  // so that an endpoint of a conformed edge always carries the canonical key.
  if (best == nullptr) return rebase(frame, coord, latitudeKey(frame, coord), latitude.keyLat);
  return best->coord;
}

void collectRange(const std::vector<BoundaryPoint>& points, double low, double high,
                  std::vector<const BoundaryPoint*>& selected)
{
  std::vector<BoundaryPoint>::const_iterator it =
      std::lower_bound(points.begin(), points.end(), low,
                       [](const BoundaryPoint& point, double value)
                       { return point.lon < value; });
  for (; it != points.end() && it->lon <= high; ++it) selected.push_back(&*it);
}

void appendInteriorPoints(const PoleFrame& frame, const LatitudeBreakpoints& latitude,
                          const Coord& a, const Coord& b, std::vector<Coord>& output)
{
  const double start = azimuth(frame, a);
  const double delta = longitudeDelta(frame, a, b);
  const double span = std::fabs(delta);
  if (span <= LON_TOL) return;

  std::vector<const BoundaryPoint*> selected;
  if (delta > 0.0)
  {
    const double end = start+span;
    if (end < TWO_PI) collectRange(latitude.points, start, end, selected);
    else
    {
      collectRange(latitude.points, start, TWO_PI, selected);
      collectRange(latitude.points, 0.0, end-TWO_PI, selected);
    }
  }
  else
  {
    const double end = start-span;
    if (end >= 0.0) collectRange(latitude.points, end, start, selected);
    else
    {
      collectRange(latitude.points, 0.0, start, selected);
      collectRange(latitude.points, end+TWO_PI, TWO_PI, selected);
    }
  }

  std::vector<std::pair<double, Coord> > interior;
  for (size_t i = 0; i < selected.size(); ++i)
  {
    double distance = delta > 0.0 ? selected[i]->lon-start : start-selected[i]->lon;
    if (distance < 0.0) distance += TWO_PI;
    if (distance > LON_TOL && distance < span-LON_TOL)
      interior.push_back(std::make_pair(distance, selected[i]->coord));
  }
  std::sort(interior.begin(), interior.end(), [](const std::pair<double, Coord>& lhs,
                                                  const std::pair<double, Coord>& rhs)
  {
    if (lhs.first != rhs.first) return lhs.first < rhs.first;
    return coordLess(lhs.second, rhs.second);
  });
  for (size_t i = 0; i < interior.size(); ++i) output.push_back(interior[i].second);
}

void conformElement(const PoleFrame& frame, Elt& element, const Registry& registry)
{
  std::vector<Coord> snapped = element.vertex;
  std::vector<const LatitudeBreakpoints*> edgeLatitude(element.n, nullptr);

  for (int i = 0; i < element.n; ++i)
  {
    const int next = (i+1)%element.n;
    if (!isSmallCircleEdge(frame, element.vertex[i], element.vertex[next])) continue;
    const LatitudeBreakpoints* latitude = findLatitude(registry, latitudeKey(frame, element.vertex[i]));
    // Both endpoints must have been grouped into the same latitude, otherwise this
    // edge straddles a bucket boundary and is left exactly as the caller built it.
    if (latitude == nullptr ||
        latitude != findLatitude(registry, latitudeKey(frame, element.vertex[next]))) continue;
    edgeLatitude[i] = latitude;
    snapped[i] = snap(frame, *latitude, element.vertex[i]);
    snapped[next] = snap(frame, *latitude, element.vertex[next]);
  }

  std::vector<Coord> vertices;
  vertices.reserve(element.n);
  bool changed = false;
  for (int i = 0; i < element.n; ++i)
  {
    vertices.push_back(snapped[i]);
    if (!(snapped[i] == element.vertex[i])) changed = true;
    if (edgeLatitude[i] != nullptr)
    {
      const size_t oldSize = vertices.size();
      appendInteriorPoints(frame, *edgeLatitude[i], snapped[i], snapped[(i+1)%element.n], vertices);
      if (vertices.size() != oldSize) changed = true;
    }
  }

  std::vector<Coord> compact;
  compact.reserve(vertices.size());
  for (size_t i = 0; i < vertices.size(); ++i)
    if (compact.empty() || !(vertices[i] == compact.back())) compact.push_back(vertices[i]);
  if (compact.size() > 1 && compact.front() == compact.back()) compact.pop_back();
  if (compact.size() != vertices.size()) changed = true;

  if (changed)
  {
    element.vertex.swap(compact);
    element.n = static_cast<int>(element.vertex.size());
    element.allocate();
    element.x = barycentre(element.vertex.data(), element.n);
  }
}

}

void conformSharedLatitudeBoundaries(
    std::vector<Elt>& elements,
    MPI_Comm communicator,
    const Coord& pole,
    const double* fullBoundsLon,
    const double* fullBoundsLat,
    int nVertex,
    int fullNbCells)
{
  // normals() classifies every edge of a pole == ORIGIN domain as a great circle,
  // so there is no small-circle boundary to conform. `pole` is a domain attribute
  // and is identical on every rank, so returning here keeps the collectives below
  // rank-consistent.
  if (pole == ORIGIN) return;

  const PoleFrame frame = makePoleFrame(pole);

  bool invalidSpan = false;
  const std::vector<Coord> local = collectLocalEndpoints(
      frame, elements, fullBoundsLon, fullBoundsLat, nVertex, fullNbCells, invalidSpan);
  int localInvalidSpan = invalidSpan ? 1 : 0;
  int globalInvalidSpan = 0;
  MPI_Allreduce(&localInvalidSpan, &globalInvalidSpan, 1, MPI_INT, MPI_MAX, communicator);
  if (globalInvalidSpan != 0)
    throw std::runtime_error("conformSharedLatitudeBoundaries: small-circle edge spans at least pi-LON_TOL");
  const std::vector<Coord> global = exchangeEndpoints(local, communicator);
  const Registry registry = buildRegistry(frame, global);
  for (std::vector<Elt>::iterator it = elements.begin(); it != elements.end(); ++it)
    conformElement(frame, *it, registry);
}

}
