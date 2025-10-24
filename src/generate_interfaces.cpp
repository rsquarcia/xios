#include "xios.hpp"
#include "generate_interface.hpp"
#include "indent.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "node_type.hpp"

using namespace xios;


int main (int argc, char ** argv, char ** UNUSED (env))
{
  // string path="./src/attr_interface/";
  string path="./interface/";

  CContext* context=CContext::create("interface");
  CCalendarWrapper calendar_wrapper(context);


  CScalar scalar(context);
  CScalarGroup scalargroup(context);
  CAxis axis(context);
  CAxisGroup axisgroup(context);
  CField field(context);
  CFieldGroup fieldgroup(context);
  CVariable variable(context);
  CVariableGroup variablegroup(context);
  CDomain domain(context);
  CDomainGroup domaingroup(context);
  CGrid grid(context);
  CGridGroup gridgroup(context);
  CFile file(context);
  CFileGroup filegroup(context);
  CInterpolateDomain interpolate_domain(context);
  CZoomDomain zoom_domain(context);
  CGenerateRectilinearDomain generate_rectilinear_domain(context);
  CComputeConnectivityDomain compute_connectivity_domain(context);
  CExpandDomain expand_domain(context);
  CReorderDomain reorder_domain(context);
  CExtractDomain extract_domain(context);
  CInterpolateAxis interpolate_axis(context);
  CZoomAxis zoom_axis(context);
  CInverseAxis inverse_axis(context);
  CExtractAxis extract_axis(context);
  CReduceDomainToAxis reduce_domain_to_axis(context);
  CReduceAxisToAxis reduce_axis_to_axis(context);
  CExtractDomainToAxis extract_domain_to_axis(context);
  CTemporalSplitting temporal_splitting(context);
  CReduceAxisToScalar reduce_axis_to_scalar(context);
  CExtractAxisToScalar extract_axis_to_scalar(context);
  CReduceDomainToScalar reduce_domain_to_scalar(context);
  CDuplicateScalarToAxis duplicate_scalar_to_axis(context);
  CReduceScalarToScalar reduce_scalar_to_scalar(context);
  CRedistributeDomain redistribute_domain(context);
  CRedistributeAxis redistribute_axis(context);
  CRedistributeScalar redistribute_scalar(context);

  ostringstream oss;
  ofstream file_;

//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////         OBJECTS

//////////////////////////////////////////////////////////////////////////////////////////////////////

  file_.open((path+"scalar_interface_attr.F90").c_str());
  scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icscalar_attr.cpp").c_str());
  scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"iscalar_attr.F90").c_str());
  scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iscalar_attr.py").c_str());
  scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oscalar_attr.py").c_str());
  scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"scalargroup_interface_attr.F90").c_str());
  scalargroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icscalargroup_attr.cpp").c_str());
  scalargroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"iscalargroup_attr.F90").c_str());
  scalargroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iscalargroup_attr.py").c_str());
  scalargroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oscalargroup_attr.py").c_str());
  scalargroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"axis_interface_attr.F90").c_str());
  axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icaxis_attr.cpp").c_str());
  axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iaxis_attr.F90").c_str());
  axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iaxis_attr.py").c_str());
  axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oaxis_attr.py").c_str());
  axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"axisgroup_interface_attr.F90").c_str());
  axisgroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icaxisgroup_attr.cpp").c_str());
  axisgroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"iaxisgroup_attr.F90").c_str());
  axisgroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iaxisgroup_attr.py").c_str());
  axisgroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oaxisgroup_attr.py").c_str());
  axisgroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"domain_interface_attr.F90").c_str());
  domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icdomain_attr.cpp").c_str());
  domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"idomain_attr.F90").c_str());
  domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"idomain_attr.py").c_str());
  domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"odomain_attr.py").c_str());
  domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"domaingroup_interface_attr.F90").c_str());
  domaingroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icdomaingroup_attr.cpp").c_str());
  domaingroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"idomaingroup_attr.F90").c_str());
  domaingroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"idomaingroup_attr.py").c_str());
  domaingroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"odomaingroup_attr.py").c_str());
  domaingroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"grid_interface_attr.F90").c_str());
  grid.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icgrid_attr.cpp").c_str());
  grid.generateCInterface(file_);
  file_.close();

  file_.open((path+"igrid_attr.F90").c_str());
  grid.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"igrid_attr.py").c_str());
  grid.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ogrid_attr.py").c_str());
  grid.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"gridgroup_interface_attr.F90").c_str());
  gridgroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icgridgroup_attr.cpp").c_str());
  gridgroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"igridgroup_attr.F90").c_str());
  gridgroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"igridgroup_attr.py").c_str());
  gridgroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ogridgroup_attr.py").c_str());
  gridgroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"field_interface_attr.F90").c_str());
  field.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icfield_attr.cpp").c_str());
  field.generateCInterface(file_);
  file_.close();

  file_.open((path+"ifield_attr.F90").c_str());
  field.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ifield_attr.py").c_str());
  field.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ofield_attr.py").c_str());
  field.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"fieldgroup_interface_attr.F90").c_str());
  fieldgroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icfieldgroup_attr.cpp").c_str());
  fieldgroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"ifieldgroup_attr.F90").c_str());
  fieldgroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ifieldgroup_attr.py").c_str());
  fieldgroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ofieldgroup_attr.py").c_str());
  fieldgroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"variable_interface_attr.F90").c_str());
  variable.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icvariable_attr.cpp").c_str());
  variable.generateCInterface(file_);
  file_.close();

  file_.open((path+"ivariable_attr.F90").c_str());
  variable.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ivariable_attr.py").c_str());
  variable.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ovariable_attr.py").c_str());
  variable.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"variablegroup_interface_attr.F90").c_str());
  variablegroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icvariablegroup_attr.cpp").c_str());
  variablegroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"ivariablegroup_attr.F90").c_str());
  variablegroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ivariablegroup_attr.py").c_str());
  variablegroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ovariablegroup_attr.py").c_str());
  variablegroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"file_interface_attr.F90").c_str());
  file.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icfile_attr.cpp").c_str());
  file.generateCInterface(file_);
  file_.close();

  file_.open((path+"ifile_attr.F90").c_str());
  file.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ifile_attr.py").c_str());
  file.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ofile_attr.py").c_str());
  file.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"filegroup_interface_attr.F90").c_str());
  filegroup.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icfilegroup_attr.cpp").c_str());
  filegroup.generateCInterface(file_);
  file_.close();

  file_.open((path+"ifilegroup_attr.F90").c_str());
  filegroup.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ifilegroup_attr.py").c_str());
  filegroup.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ofilegroup_attr.py").c_str());
  filegroup.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"calendar_wrapper_interface_attr.F90").c_str());
  calendar_wrapper.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"iccalendar_wrapper_attr.cpp").c_str());
  calendar_wrapper.generateCInterface(file_);
  file_.close();

  file_.open((path+"icalendar_wrapper_attr.F90").c_str());
  calendar_wrapper.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"icalendar_wrapper_attr.py").c_str());
  calendar_wrapper.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ocalendar_wrapper_attr.py").c_str());
  calendar_wrapper.generateObjPythonInterface(file_);
  file_.close();


//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////         DOMAIN TRANSFORMATIONS

//////////////////////////////////////////////////////////////////////////////////////////////////////

  file_.open((path+"zoom_domain_interface_attr.F90").c_str());
  zoom_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"iczoom_domain_attr.cpp").c_str());
  zoom_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"izoom_domain_attr.F90").c_str());
  zoom_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"izoom_domain_attr.py").c_str());
  zoom_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ozoom_domain_attr.py").c_str());
  zoom_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"extract_domain_interface_attr.F90").c_str());
  extract_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icextract_domain_attr.cpp").c_str());
  extract_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"iextract_domain_attr.F90").c_str());
  extract_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iextract_domain_attr.py").c_str());
  extract_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oextract_domain_attr.py").c_str());
  extract_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"interpolate_domain_interface_attr.F90").c_str());
  interpolate_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icinterpolate_domain_attr.cpp").c_str());
  interpolate_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"iinterpolate_domain_attr.F90").c_str());
  interpolate_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iinterpolate_domain_attr.py").c_str());
  interpolate_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ointerpolate_domain_attr.py").c_str());
  interpolate_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"generate_rectilinear_domain_interface_attr.F90").c_str());
  generate_rectilinear_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icgenerate_rectilinear_domain_attr.cpp").c_str());
  generate_rectilinear_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"igenerate_rectilinear_domain_attr.F90").c_str());
  generate_rectilinear_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"igenerate_rectilinear_domain_attr.py").c_str());
  generate_rectilinear_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ogenerate_rectilinear_domain_attr.py").c_str());
  generate_rectilinear_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"compute_connectivity_domain_interface_attr.F90").c_str());
  compute_connectivity_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"iccompute_connectivity_domain_attr.cpp").c_str());
  compute_connectivity_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"icompute_connectivity_domain_attr.F90").c_str());
  compute_connectivity_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"icompute_connectivity_domain_attr.py").c_str());
  compute_connectivity_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ocompute_connectivity_domain_attr.py").c_str());
  compute_connectivity_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"expand_domain_interface_attr.F90").c_str());
  expand_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icexpand_domain_attr.cpp").c_str());
  expand_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"iexpand_domain_attr.F90").c_str());
  expand_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iexpand_domain_attr.py").c_str());
  expand_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oexpand_domain_attr.py").c_str());
  expand_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"reorder_domain_interface_attr.F90").c_str());
  reorder_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreorder_domain_attr.cpp").c_str());
  reorder_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireorder_domain_attr.F90").c_str());
  reorder_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireorder_domain_attr.py").c_str());
  reorder_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreorder_domain_attr.py").c_str());
  reorder_domain.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"redistribute_domain_interface_attr.F90").c_str());
  redistribute_domain.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icredistribute_domain_attr.cpp").c_str());
  redistribute_domain.generateCInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_domain_attr.F90").c_str());
  redistribute_domain.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_domain_attr.py").c_str());
  redistribute_domain.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oredistribute_domain_attr.py").c_str());
  redistribute_domain.generateObjPythonInterface(file_);
  file_.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////         AXIS TRANSFORMATIONS

//////////////////////////////////////////////////////////////////////////////////////////////////////

  file_.open((path+"zoom_axis_interface_attr.F90").c_str());
  zoom_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"iczoom_axis_attr.cpp").c_str());
  zoom_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"izoom_axis_attr.F90").c_str());
  zoom_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"izoom_axis_attr.py").c_str());
  zoom_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ozoom_axis_attr.py").c_str());
  zoom_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"interpolate_axis_interface_attr.F90").c_str());
  interpolate_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icinterpolate_axis_attr.cpp").c_str());
  interpolate_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iinterpolate_axis_attr.F90").c_str());
  interpolate_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iinterpolate_axis_attr.py").c_str());
  interpolate_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ointerpolate_axis_attr.py").c_str());
  interpolate_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"inverse_axis_interface_attr.F90").c_str());
  inverse_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icinverse_axis_attr.cpp").c_str());
  inverse_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iinverse_axis_attr.F90").c_str());
  inverse_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iinverse_axis_attr.py").c_str());
  inverse_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oinverse_axis_attr.py").c_str());
  inverse_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"reduce_domain_to_axis_interface_attr.F90").c_str());
  reduce_domain_to_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreduce_domain_to_axis_attr.cpp").c_str());
  reduce_domain_to_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireduce_domain_to_axis_attr.F90").c_str());
  reduce_domain_to_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireduce_domain_to_axis_attr.py").c_str());
  reduce_domain_to_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreduce_domain_to_axis_attr.py").c_str());
  reduce_domain_to_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"reduce_axis_to_axis_interface_attr.F90").c_str());
  reduce_axis_to_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreduce_axis_to_axis_attr.cpp").c_str());
  reduce_axis_to_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireduce_axis_to_axis_attr.F90").c_str());
  reduce_axis_to_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireduce_axis_to_axis_attr.py").c_str());
  reduce_axis_to_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreduce_axis_to_axis_attr.py").c_str());
  reduce_axis_to_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"extract_domain_to_axis_interface_attr.F90").c_str());
  extract_domain_to_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icextract_domain_to_axis_attr.cpp").c_str());
  extract_domain_to_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iextract_domain_to_axis_attr.F90").c_str());
  extract_domain_to_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iextract_domain_to_axis_attr.py").c_str());
  extract_domain_to_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oextract_domain_to_axis_attr.py").c_str());
  extract_domain_to_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"temporal_splitting_interface_attr.F90").c_str());
  temporal_splitting.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"ictemporal_splitting_attr.cpp").c_str());
  temporal_splitting.generateCInterface(file_);
  file_.close();

  file_.open((path+"itemporal_splitting_attr.F90").c_str());
  temporal_splitting.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"itemporal_splitting_attr.py").c_str());
  temporal_splitting.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"otemporal_splitting_attr.py").c_str());
  temporal_splitting.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"duplicate_scalar_to_axis_interface_attr.F90").c_str());
  duplicate_scalar_to_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icduplicate_scalar_to_axis_attr.cpp").c_str());
  duplicate_scalar_to_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iduplicate_scalar_to_axis_attr.F90").c_str());
  duplicate_scalar_to_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iduplicate_scalar_to_axis_attr.py").c_str());
  duplicate_scalar_to_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oduplicate_scalar_to_axis_attr.py").c_str());
  duplicate_scalar_to_axis.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"redistribute_axis_interface_attr.F90").c_str());
  redistribute_axis.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icredistribute_axis_attr.cpp").c_str());
  redistribute_axis.generateCInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_axis_attr.F90").c_str());
  redistribute_axis.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_axis_attr.py").c_str());
  redistribute_axis.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oredistribute_axis_attr.py").c_str());
  redistribute_axis.generateObjPythonInterface(file_);
  file_.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////         SCALAR TRANSFORMATIONS

//////////////////////////////////////////////////////////////////////////////////////////////////////

  file_.open((path+"reduce_axis_to_scalar_interface_attr.F90").c_str());
  reduce_axis_to_scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreduce_axis_to_scalar_attr.cpp").c_str());
  reduce_axis_to_scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireduce_axis_to_scalar_attr.F90").c_str());
  reduce_axis_to_scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireduce_axis_to_scalar_attr.py").c_str());
  reduce_axis_to_scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreduce_axis_to_scalar_attr.py").c_str());
  reduce_axis_to_scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"extract_axis_to_scalar_interface_attr.F90").c_str());
  extract_axis_to_scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icextract_axis_to_scalar_attr.cpp").c_str());
  extract_axis_to_scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"iextract_axis_to_scalar_attr.F90").c_str());
  extract_axis_to_scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iextract_axis_to_scalar_attr.py").c_str());
  extract_axis_to_scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oextract_axis_to_scalar_attr.py").c_str());
  extract_axis_to_scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"reduce_domain_to_scalar_interface_attr.F90").c_str());
  reduce_domain_to_scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreduce_domain_to_scalar_attr.cpp").c_str());
  reduce_domain_to_scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireduce_domain_to_scalar_attr.F90").c_str());
  reduce_domain_to_scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireduce_domain_to_scalar_attr.py").c_str());
  reduce_domain_to_scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreduce_domain_to_scalar_attr.py").c_str());
  reduce_domain_to_scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"reduce_scalar_to_scalar_interface_attr.F90").c_str());
  reduce_scalar_to_scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icreduce_scalar_to_scalar_attr.cpp").c_str());
  reduce_scalar_to_scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"ireduce_scalar_to_scalar_attr.F90").c_str());
  reduce_scalar_to_scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"ireduce_scalar_to_scalar_attr.py").c_str());
  reduce_scalar_to_scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oreduce_scalar_to_scalar_attr.py").c_str());
  reduce_scalar_to_scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"redistribute_scalar_interface_attr.F90").c_str());
  redistribute_scalar.generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"icredistribute_scalar_attr.cpp").c_str());
  redistribute_scalar.generateCInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_scalar_attr.F90").c_str());
  redistribute_scalar.generateFortranInterface(file_);
  file_.close();

  file_.open((path+"iredistribute_scalar_attr.py").c_str());
  redistribute_scalar.generatePythonInterface(file_);
  file_.close();

  file_.open((path+"oredistribute_scalar_attr.py").c_str());
  redistribute_scalar.generateObjPythonInterface(file_);
  file_.close();

  file_.open((path+"context_interface_attr.F90").c_str());
  context->generateFortran2003Interface(file_);
  file_.close();

  file_.open((path+"iccontext_attr.cpp").c_str());
  context->generateCInterface(file_);
  file_.close();

  file_.open((path+"icontext_attr.F90").c_str());
  context->generateFortranInterface(file_);
  file_.close();

  file_.open((path+"icontext_attr.py").c_str());
  context->generatePythonInterface(file_);
  file_.close();

  file_.open((path+"ocontext_attr.py").c_str());
  context->generateObjPythonInterface(file_);
  file_.close();


  return 0;
}
