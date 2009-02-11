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

#include <portinfo>

//#include "Quadrature3D.hh" // implementation of class methods

#include "CellGeometry.hh" // USES CellGeometry

#include "petsc.h" // USES PetscLogFlops

#include <cassert> // USES assert()

#define ISOPARAMETRIC

// ----------------------------------------------------------------------
// Constructor
template<typename mesh_type>
pylith::feassemble::Quadrature3D<mesh_type>::Quadrature3D(void) : pylith::feassemble::Quadrature::Quadrature()
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
template<typename mesh_type>
pylith::feassemble::Quadrature3D<mesh_type>::~Quadrature3D(void)
{ // destructor
} // destructor
  
// ----------------------------------------------------------------------
// Copy constructor.
template<typename mesh_type>
pylith::feassemble::Quadrature3D<mesh_type>::Quadrature3D(const Quadrature3D& q) :
  Quadrature(q)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Compute geometric quantities for a cell at quadrature points.
template<typename mesh_type>
void
pylith::feassemble::Quadrature3D<mesh_type>::computeGeometry(
					           const double* vertCoords,
						   const int coordDim,
						   const int cell)
{ // computeGeometry
  assert(3 == _cellDim);
  assert(3 == _spaceDim);

  _resetGeometry();
  assert(3 == coordDim);

  // Loop over quadrature points
  for (int iQuadPt=0; iQuadPt < _numQuadPts; ++iQuadPt) {
    
    // Compute coordinates of quadrature point in cell
#if defined(ISOPARAMETRIC)
    // x = sum[i=0,n-1] (Ni * xi)
    // y = sum[i=0,n-1] (Ni * yi)
    // z = sum[i=0,n-1] (Ni * zi)
    for (int iBasis=0; iBasis < _numBasis; ++iBasis) {
      const double basis = _basis[iQuadPt*_numBasis+iBasis];
      for (int iDim=0; iDim < _spaceDim; ++iDim)
	_quadPts[iQuadPt*_spaceDim+iDim] += 
	  basis * vertCoords[iBasis*_spaceDim+iDim];
    } // for
#else
    assert(0 != _geometry);
    _geometry->coordsRefToGlobal(&_quadPts[iQuadPt*_spaceDim],
				 &_quadPtsRef[iQuadPt*_cellDim],
				 vertCoords, _spaceDim);
#endif
    
#if defined(ISOPARAMETRIC)
    // Compute Jacobian at quadrature point
    // J = [dx/dp dx/dq dx/dr]
    //     [dy/dp dy/dq dy/dr]
    //     [dz/dp dz/dq dz/dr]
    // dx/dp = sum[i=0,n-1] (dNi/dp * xi)
    // dx/dq = sum[i=0,n-1] (dNi/dq * xi)
    // dx/dr = sum[i=0,n-1] (dNi/dr * xi)
    // dy/dp = sum[i=0,n-1] (dNi/dp * yi)
    // dy/dq = sum[i=0,n-1] (dNi/dq * yi)
    // dy/dr = sum[i=0,n-1] (dNi/dr * yi)
    // dz/dp = sum[i=0,n-1] (dNi/dp * zi)
    // dz/dq = sum[i=0,n-1] (dNi/dq * zi)
    // dz/dr = sum[i=0,n-1] (dNi/dr * zi)
    for (int iBasis=0; iBasis < _numBasis; ++iBasis)
      for (int iCol=0; iCol < _cellDim; ++iCol) {
	const double deriv = 
	  _basisDerivRef[iQuadPt*_numBasis*_spaceDim+iBasis*_cellDim+iCol];
	for (int iRow=0; iRow < _spaceDim; ++iRow)
	  _jacobian[iQuadPt*_cellDim*_spaceDim+iRow*_cellDim+iCol] += 
	    deriv * vertCoords[iBasis*_spaceDim+iRow];
      } // for

    // Compute determinant of Jacobian at quadrature point
    // |J| = j00*(j11*j22-j12*j21) +
    //      -j01*(j10*j22-j12*j20) +
    //       j02*(j10*j21-j11*j20)
    const int iJ = iQuadPt*_cellDim*_spaceDim;
    const int i00 = iJ + 0*_spaceDim + 0;
    const int i01 = iJ + 0*_spaceDim + 1;
    const int i02 = iJ + 0*_spaceDim + 2;
    const int i10 = iJ + 1*_spaceDim + 0;
    const int i11 = iJ + 1*_spaceDim + 1;
    const int i12 = iJ + 1*_spaceDim + 2;
    const int i20 = iJ + 2*_spaceDim + 0;
    const int i21 = iJ + 2*_spaceDim + 1;
    const int i22 = iJ + 2*_spaceDim + 2;
    const double det = 
      _jacobian[i00]*(_jacobian[i11]*_jacobian[i22] -
		      _jacobian[i12]*_jacobian[i21]) -
      _jacobian[i01]*(_jacobian[i10]*_jacobian[i22] -
		      _jacobian[i12]*_jacobian[i20]) +
      _jacobian[i02]*(_jacobian[i10]*_jacobian[i21] -
		      _jacobian[i11]*_jacobian[i20]);
    _checkJacobianDet(det, cell);
    _jacobianDet[iQuadPt] = det;
#else
    // Compute Jacobian and determinant of Jacobian at quadrature point
    assert(0 != _geometry);
    _geometry->jacobian(&_jacobian[iQuadPt*_cellDim*_spaceDim],
			&_jacobianDet[iQuadPt],
			vertCoords, &_quadPtsRef[iQuadPt*_cellDim], _spaceDim);
    _checkJacobianDet(_jacobianDet[iQuadPt], cell);

    const int iJ = iQuadPt*_cellDim*_spaceDim;
    const int i00 = iJ + 0*_spaceDim + 0;
    const int i01 = iJ + 0*_spaceDim + 1;
    const int i02 = iJ + 0*_spaceDim + 2;
    const int i10 = iJ + 1*_spaceDim + 0;
    const int i11 = iJ + 1*_spaceDim + 1;
    const int i12 = iJ + 1*_spaceDim + 2;
    const int i20 = iJ + 2*_spaceDim + 0;
    const int i21 = iJ + 2*_spaceDim + 1;
    const int i22 = iJ + 2*_spaceDim + 2;
    const double det = _jacobianDet[iQuadPt];
#endif
    
    // Compute inverse of Jacobian at quadrature point
    _jacobianInv[i00] = (_jacobian[i11]*_jacobian[i22] -
			 _jacobian[i12]*_jacobian[i21]) / det;
    _jacobianInv[i01] = (_jacobian[i02]*_jacobian[i21] -
			 _jacobian[i01]*_jacobian[i22]) / det;
    _jacobianInv[i02] = (_jacobian[i01]*_jacobian[i12] -
			 _jacobian[i02]*_jacobian[i11]) / det;
    _jacobianInv[i10] = (_jacobian[i12]*_jacobian[i20] -
			 _jacobian[i10]*_jacobian[i22]) / det;
    _jacobianInv[i11] = (_jacobian[i00]*_jacobian[i22] -
			 _jacobian[i02]*_jacobian[i20]) / det;
    _jacobianInv[i12] = (_jacobian[i02]*_jacobian[i10] -
			 _jacobian[i00]*_jacobian[i12]) / det;
    _jacobianInv[i20] = (_jacobian[i10]*_jacobian[i21] -
			 _jacobian[i11]*_jacobian[i20]) / det;
    _jacobianInv[i21] = (_jacobian[i01]*_jacobian[i20] -
			 _jacobian[i00]*_jacobian[i21]) / det;
    _jacobianInv[i22] = (_jacobian[i00]*_jacobian[i11] -
			 _jacobian[i01]*_jacobian[i10]) / det;

    // Compute derivatives of basis functions with respect to global
    // coordinates
    // dNi/dx = dNi/dp dp/dx + dNi/dq dq/dx + dNi/dr dr/dx
    for (int iBasis=0; iBasis < _numBasis; ++iBasis)
      for (int iDim=0; iDim < _spaceDim; ++iDim)
	for (int jDim=0; jDim < _cellDim; ++jDim)
	  _basisDeriv[iQuadPt*_numBasis*_spaceDim+iBasis*_spaceDim+iDim] +=
	    _basisDerivRef[iQuadPt*_numBasis*_cellDim+iBasis*_cellDim+jDim] *
	    _jacobianInv[iQuadPt*_cellDim*_spaceDim+jDim*_spaceDim+iDim];
  } // for

  PetscLogFlops(_numQuadPts*(2+36 + 
				    _numBasis*_spaceDim*_cellDim*4));
} // computeGeometry


// End of file 
