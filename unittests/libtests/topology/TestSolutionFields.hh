// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

/**
 * @file unittests/libtests/topology/TestSolutionFields.hh
 *
 * @brief C++ TestSolutionFields object.
 * 
 * C++ unit testing for SolutionFields.
 */

#if !defined(pylith_topology_testsolutionfields_hh)
#define pylith_topology_testsolutionfields_hh

#include <cppunit/extensions/HelperMacros.h>

#include "pylith/topology/topologyfwd.hh"

/// Namespace for pylith package
namespace pylith {
  namespace topology {
    class TestSolutionFields;
  } // topology
} // pylith

/// C++ unit testing for SolutionFields.
class pylith::topology::TestSolutionFields : public CppUnit::TestFixture
{ // class TestSolutionFields

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSolutionFields );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testSolutionName );
  CPPUNIT_TEST( testSolution );
  CPPUNIT_TEST( testCreateHistory );
  CPPUNIT_TEST( testShiftHistory );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor.
  void testConstructor(void);

  /// Test solutionName().
  void testSolutionName(void);

  /// Test solution().
  void testSolution(void);

  /// Test createHistory().
  void testCreateHistory(void);

  /// Test shiftHistory().
  void testShiftHistory(void);

  /// Test getFieldByHistory().
  void testGetFieldByHistory(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Initialize mesh for SolutionFields.
   *
   * @param mesh Finite-element mesh.
   */
  void _initialize(Mesh* mesh) const;

}; // class TestSolutionFields

#endif // pylith_topology_solutionfields_hh


// End of file 
