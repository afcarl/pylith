// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

// DO NOT EDIT THIS FILE
// This file was generated from python application elasticstrain1d.

#include "ElasticStrain1DData.hh"

const int pylith::materials::ElasticStrain1DData::_dimension = 1;

const int pylith::materials::ElasticStrain1DData::_numLocs = 2;

const int pylith::materials::ElasticStrain1DData::_numProperties = 3;

const int pylith::materials::ElasticStrain1DData::_numStateVars = 0;

const int pylith::materials::ElasticStrain1DData::_numDBProperties = 3;

const int pylith::materials::ElasticStrain1DData::_numDBStateVars = 0;

const int pylith::materials::ElasticStrain1DData::_numPropsQuadPt = 3;

const int pylith::materials::ElasticStrain1DData::_numVarsQuadPt = 0;

const double pylith::materials::ElasticStrain1DData::_lengthScale =   1.00000000e+03;

const double pylith::materials::ElasticStrain1DData::_timeScale =   1.00000000e+00;

const double pylith::materials::ElasticStrain1DData::_pressureScale =   2.25000000e+10;

const double pylith::materials::ElasticStrain1DData::_densityScale =   1.00000000e+03;

const double pylith::materials::ElasticStrain1DData::_dtStableImplicit =   1.00000000e+30;

const int pylith::materials::ElasticStrain1DData::_numPropertyValues[] = {
1,
1,
1,
};

const int* pylith::materials::ElasticStrain1DData::_numStateVarValues = 0;

const char* pylith::materials::ElasticStrain1DData::_dbPropertyValues[] = {
"density",
"vs",
"vp",
};

const char** pylith::materials::ElasticStrain1DData::_dbStateVarValues = 0;

const double pylith::materials::ElasticStrain1DData::_dbProperties[] = {
  2.50000000e+03,
  3.00000000e+03,
  5.19615242e+03,
  2.00000000e+03,
  1.20000000e+03,
  2.07846097e+03,
};

const double* pylith::materials::ElasticStrain1DData::_dbStateVars = 0;

const double pylith::materials::ElasticStrain1DData::_properties[] = {
  2.50000000e+03,
  2.25000000e+10,
  2.25000000e+10,
  2.00000000e+03,
  2.88000000e+09,
  2.88000000e+09,
};

const double* pylith::materials::ElasticStrain1DData::_stateVars = 0;

const double pylith::materials::ElasticStrain1DData::_propertiesNondim[] = {
  2.50000000e+00,
  1.00000000e+00,
  1.00000000e+00,
  2.00000000e+00,
  1.28000000e-01,
  1.28000000e-01,
};

const double* pylith::materials::ElasticStrain1DData::_stateVarsNondim = 0;

const double pylith::materials::ElasticStrain1DData::_density[] = {
  2.50000000e+03,
  2.00000000e+03,
};

const double pylith::materials::ElasticStrain1DData::_strain[] = {
  1.10000000e-04,
  4.10000000e-04,
};

const double pylith::materials::ElasticStrain1DData::_stress[] = {
  2.83710000e+07,
  8.86380000e+06,
};

const double pylith::materials::ElasticStrain1DData::_elasticConsts[] = {
  6.75000000e+10,
  8.64000000e+09,
};

const double pylith::materials::ElasticStrain1DData::_initialStress[] = {
  2.10000000e+04,
  5.10000000e+04,
};

const double pylith::materials::ElasticStrain1DData::_initialStrain[] = {
  3.10000000e-04,
  6.10000000e-04,
};

const double* pylith::materials::ElasticStrain1DData::_stateVarsUpdated = 0;

pylith::materials::ElasticStrain1DData::ElasticStrain1DData(void)
{ // constructor
  dimension = _dimension;
  numLocs = _numLocs;
  numProperties = _numProperties;
  numStateVars = _numStateVars;
  numDBProperties = _numDBProperties;
  numDBStateVars = _numDBStateVars;
  numPropsQuadPt = _numPropsQuadPt;
  numVarsQuadPt = _numVarsQuadPt;
  lengthScale = _lengthScale;
  timeScale = _timeScale;
  pressureScale = _pressureScale;
  densityScale = _densityScale;
  dtStableImplicit = _dtStableImplicit;
  numPropertyValues = const_cast<int*>(_numPropertyValues);
  numStateVarValues = const_cast<int*>(_numStateVarValues);
  dbPropertyValues = const_cast<char**>(_dbPropertyValues);
  dbStateVarValues = const_cast<char**>(_dbStateVarValues);
  dbProperties = const_cast<double*>(_dbProperties);
  dbStateVars = const_cast<double*>(_dbStateVars);
  properties = const_cast<double*>(_properties);
  stateVars = const_cast<double*>(_stateVars);
  propertiesNondim = const_cast<double*>(_propertiesNondim);
  stateVarsNondim = const_cast<double*>(_stateVarsNondim);
  density = const_cast<double*>(_density);
  strain = const_cast<double*>(_strain);
  stress = const_cast<double*>(_stress);
  elasticConsts = const_cast<double*>(_elasticConsts);
  initialStress = const_cast<double*>(_initialStress);
  initialStrain = const_cast<double*>(_initialStrain);
  stateVarsUpdated = const_cast<double*>(_stateVarsUpdated);
} // constructor

pylith::materials::ElasticStrain1DData::~ElasticStrain1DData(void)
{}


// End of file
