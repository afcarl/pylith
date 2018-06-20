// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/materials/IsotropicLinearMaxwell3D.hh
 *
 * @brief C++ class for isotropic linear Maxwell viscoelastic 3D material.
 */

#if !defined(pylith_materials_isotropiclinearmaxwell3d_hh)
#define pylith_materials_isotropiclinearmaxwell3d_hh

// Include directives ---------------------------------------------------
#include "materialsfwd.hh" // forward declarations

#include "pylith/materials/Material.hh" // ISA Material

// Material -------------------------------------------------------------
/** @brief C++ class for isotropic linear Maxwell viscoelastic 3D material.
 */

class pylith::materials::IsotropicLinearMaxwell3D : public pylith::materials::Material { // class IsotropicLinearMaxwell3D
    friend class TestIsotropicLinearMaxwell3D;   // unit testing

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Default constructor.
    IsotropicLinearMaxwell3D(void);

    /// Destructor.
    ~IsotropicLinearMaxwell3D(void);

    /** Include inertia?
     *
     * @param[in] value Flag indicating to include inertial term.
     */
    void useInertia(const bool value);

    /** Include inertia?
     *
     * @returns True if including inertial term, false otherwise.
     */
    bool useInertia(void) const;

    /** Include body force?
     *
     * @param[in] value Flag indicating to include body force term.
     */
    void useBodyForce(const bool value);

    /** Include body force?
     *
     * @returns True if including body force term, false otherwise.
     */
    bool useBodyForce(void) const;

    /** Use reference stress and strain in computation of stress and
     * strain?
     *
     * @param[in] value Flag indicating to include reference stress and strain.
     */
    void useReferenceState(const bool value);

    /** Use reference stress and strain in computation of stress and
     * strain?
     *
     * @returns True if using reference stress and strain, false otherwise.
     */
    bool useReferenceState(void) const;

    /** Verify configuration is acceptable.
     *
     * @param[in] solution Solution field.
     */
    void verifyConfiguration(const pylith::topology::Field& solution) const;

    // PROTECTED METHODS //////////////////////////////////////////////////
protected:

    /// Setup auxiliary subfields (discretization and query fns).
    void _auxFieldSetup(void);

    /** Set finite-element constants.
     *
     * @param[inout] solution Solution field.
     * @param[in] dt Time step size for current time step.
     */
    void _setFEConstants(const pylith::topology::Field& solution,
                         const PylithReal dt) const;

    /** Set kernels for RHS residual G(t,u).
     *
     * @param[in] solution Solution field.
     */
    void _setFEKernelsRHSResidual(const topology::Field& solution) const;

    /** Set kernels for RHS Jacobian G(t,u).
     *
     * @param[in] solution Solution field.
     */
    void _setFEKernelsRHSJacobian(const topology::Field& solution) const;

    /** Set kernels for LHS residual F(t,u,\dot{u}).
     *
     * @param[in] solution Solution field.
     */
    void _setFEKernelsLHSResidual(const topology::Field& solution) const;


    /** Set kernels for LHS Jacobian F(t,u,\dot{u}).
     *
     * @param[in] solution Solution field.
     */
    void _setFEKernelsLHSJacobian(const topology::Field& solution) const;


    // PRIVATE MEMBERS ////////////////////////////////////////////////////
private:

    bool _useInertia;   ///< Flag to include inertial term.
    bool _useBodyForce;   ///< Flag to include body force term.
    bool _useReferenceState;   ///< Flag to use reference stress and strain.

    static const char* _pyreComponent; ///< Name of Pyre component.

    // NOT IMPLEMENTED ////////////////////////////////////////////////////
private:

    IsotropicLinearMaxwell3D(const IsotropicLinearMaxwell3D&);   ///< Not implemented.
    const IsotropicLinearMaxwell3D& operator=(const IsotropicLinearMaxwell3D&);   ///< Not implemented

}; // class IsotropicLinearMaxwell3D

#endif // pylith_materials_isotropiclinearmaxwell3d_hh


// End of file