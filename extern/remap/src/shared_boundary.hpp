#ifndef __SHARED_BOUNDARY_HPP__
#define __SHARED_BOUNDARY_HPP__

#include "elt.hpp"
#include "mpi.hpp"

#include <vector>

namespace sphereRemap {

/** Make the two owners of a shared small-circle boundary describe that boundary
    with bit-identical coordinates.

    `pole` must be the pole these elements are given to normals()/cptEltGeom
    with. Edge eligibility is decided with exactly the criterion normals() uses
    (elt.hpp), so the registry and the geometry classifier agree by construction;
    in particular pole == ORIGIN makes every edge a great circle and this call a
    no-op.

    When `fullBoundsLon`/`fullBoundsLat` are supplied they must describe the
    complete, pre-mask cell set of this rank. They act as a geometry provider
    only: they contribute breakpoints, so that a boundary next to a masked cell
    is canonicalised the same way as one that is not, and they never contribute a
    cell, a value or a weight. */
void conformSharedLatitudeBoundaries(
    std::vector<Elt>& elements,
    MPI_Comm communicator,
    const Coord& pole,
    const double* fullBoundsLon = nullptr,
    const double* fullBoundsLat = nullptr,
    int nVertex = 0,
    int fullNbCells = 0);

}

#endif
