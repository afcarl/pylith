/* -*- C -*-
 *
 * ----------------------------------------------------------------------
 *
 * Brad T. Aagaard, U.S. Geological Survey
 * Charles A. Williams, GNS Science
 * Matthew G. Knepley, University of Chicago
 *
 * This code was developed as part of the Computational Infrastructure
 * for Geodynamics (http:*geodynamics.org).
 *
 * Copyright (c) 2010-2015 University of California, Davis
 *
 * See COPYING for license information.
 *
 * ----------------------------------------------------------------------
 */

#include <portinfo>

#include "pylith/fekernels/NeumannTimeDependent.hh"

#include <cassert> // USES assert()

/* ======================================================================
 * Kernels for computing value from parameters for time-dependent boundary conditions.
 * ======================================================================
 */

/* ----------------------------------------------------------------------
 * Scalar initial value term for time-dependent boundary condition.
 *
 * f_0(x)
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initial_scalar(const PylithInt dim,
                                                           const PylithInt numS,
                                                           const PylithInt numA,
                                                           const PylithInt sOff[],
                                                           const PylithInt sOff_x[],
                                                           const PylithScalar s[],
                                                           const PylithScalar s_t[],
                                                           const PylithScalar s_x[],
                                                           const PylithInt aOff[],
                                                           const PylithInt aOff_x[],
                                                           const PylithScalar a[],
                                                           const PylithScalar a_t[],
                                                           const PylithScalar a_x[],
                                                           const PylithReal t,
                                                           const PylithReal x[],
                                                           const PylithReal n[],
                                                           const PylithInt numConstants,
                                                           const PylithScalar constants[],
                                                           PylithScalar g0[]) {
    const PylithInt _numA = 1;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = aOff[0];

    g0[0] += a[i_initial];
} // g0_initial_scalar

/* ----------------------------------------------------------------------
 * Vector initial value term for time-dependent boundary condition.
 *
 * f_0(x)
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initial_vector(const PylithInt dim,
                                                           const PylithInt numS,
                                                           const PylithInt numA,
                                                           const PylithInt sOff[],
                                                           const PylithInt sOff_x[],
                                                           const PylithScalar s[],
                                                           const PylithScalar s_t[],
                                                           const PylithScalar s_x[],
                                                           const PylithInt aOff[],
                                                           const PylithInt aOff_x[],
                                                           const PylithScalar a[],
                                                           const PylithScalar a_t[],
                                                           const PylithScalar a_x[],
                                                           const PylithReal t,
                                                           const PylithReal x[],
                                                           const PylithReal n[],
                                                           const PylithInt numConstants,
                                                           const PylithScalar constants[],
                                                           PylithScalar g0[]) {
    const PylithInt _numA = 1;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = aOff[0];

    for (PylithInt i = 0; i < dim; ++i) {
        g0[i] += a[i_initial+i];
    } // for
} // g0_initial_vector

/* ----------------------------------------------------------------------
 * Scalar rate term for time-dependent boundary condition.
 *
 * \dot{f}_1(x) * (t-t_1(x)) for t >= t_1(x).
 */
void
pylith::fekernels::NeumannTimeDependent::g0_rate_scalar(const PylithInt dim,
                                                        const PylithInt numS,
                                                        const PylithInt numA,
                                                        const PylithInt sOff[],
                                                        const PylithInt sOff_x[],
                                                        const PylithScalar s[],
                                                        const PylithScalar s_t[],
                                                        const PylithScalar s_x[],
                                                        const PylithInt aOff[],
                                                        const PylithInt aOff_x[],
                                                        const PylithScalar a[],
                                                        const PylithScalar a_t[],
                                                        const PylithScalar a_x[],
                                                        const PylithReal t,
                                                        const PylithReal x[],
                                                        const PylithReal n[],
                                                        const PylithInt numConstants,
                                                        const PylithScalar constants[],
                                                        PylithScalar g0[]) {
    const PylithInt _numA = 2;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_rate = aOff[0];
    const PylithInt i_start = aOff[1];

    const PylithScalar tRel = t - a[i_start];
    if (tRel > 0.0) {
        g0[0] += a[i_rate]*tRel;
    } // if/else

} // g0_rate_scalar

/* ----------------------------------------------------------------------
** Vector rate term for time-dependent boundary condition.
*
* \dot{f}_1(x) * (t-t_1(x)) for t >= t_1(x).
*/
void
pylith::fekernels::NeumannTimeDependent::g0_rate_vector(const PylithInt dim,
                                                        const PylithInt numS,
                                                        const PylithInt numA,
                                                        const PylithInt sOff[],
                                                        const PylithInt sOff_x[],
                                                        const PylithScalar s[],
                                                        const PylithScalar s_t[],
                                                        const PylithScalar s_x[],
                                                        const PylithInt aOff[],
                                                        const PylithInt aOff_x[],
                                                        const PylithScalar a[],
                                                        const PylithScalar a_t[],
                                                        const PylithScalar a_x[],
                                                        const PylithReal t,
                                                        const PylithReal x[],
                                                        const PylithReal n[],
                                                        const PylithInt numConstants,
                                                        const PylithScalar constants[],
                                                        PylithScalar g0[]) {
    const PylithInt _numA = 2;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_rate = aOff[0];
    const PylithInt i_start = aOff[1];

    const PylithScalar tRel = t - a[i_start];
    if (tRel > 0.0) {
        for (PylithInt i = 0; i < dim; ++i) {
            g0[i] += a[i_rate+i]*tRel;
        } // for
    } // if/else
} // g0_rate_vector


/* ----------------------------------------------------------------------
 * Scalar time history term for time-dependent boundary condition.
 *
 * f_2(x) * a(t-t_2(x)) for t >= t_2(x).
 */
void
pylith::fekernels::NeumannTimeDependent::g0_timeHistory_scalar(const PylithInt dim,
                                                               const PylithInt numS,
                                                               const PylithInt numA,
                                                               const PylithInt sOff[],
                                                               const PylithInt sOff_x[],
                                                               const PylithScalar s[],
                                                               const PylithScalar s_t[],
                                                               const PylithScalar s_x[],
                                                               const PylithInt aOff[],
                                                               const PylithInt aOff_x[],
                                                               const PylithScalar a[],
                                                               const PylithScalar a_t[],
                                                               const PylithScalar a_x[],
                                                               const PylithReal t,
                                                               const PylithReal x[],
                                                               const PylithReal n[],
                                                               const PylithInt numConstants,
                                                               const PylithScalar constants[],
                                                               PylithScalar g0[]) {
    const PylithInt _numA = 3;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_amplitude = aOff[0];
    const PylithInt i_value = aOff[2];

    g0[0] += a[i_amplitude]*a[i_value];
} // g0_timeHistory_scalar

/* ----------------------------------------------------------------------
 * Vector time history term for time-dependent boundary condition.
 *
 * f_2(x) * a(t-t_2(x)) for t >= t_2(x).
 */
void
pylith::fekernels::NeumannTimeDependent::g0_timeHistory_vector(const PylithInt dim,
                                                               const PylithInt numS,
                                                               const PylithInt numA,
                                                               const PylithInt sOff[],
                                                               const PylithInt sOff_x[],
                                                               const PylithScalar s[],
                                                               const PylithScalar s_t[],
                                                               const PylithScalar s_x[],
                                                               const PylithInt aOff[],
                                                               const PylithInt aOff_x[],
                                                               const PylithScalar a[],
                                                               const PylithScalar a_t[],
                                                               const PylithScalar a_x[],
                                                               const PylithReal t,
                                                               const PylithReal x[],
                                                               const PylithReal n[],
                                                               const PylithInt numConstants,
                                                               const PylithScalar constants[],
                                                               PylithScalar g0[]) {
    const PylithInt _numA = 3;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_amplitude = aOff[0];
    const PylithInt i_value = aOff[2];

    for (PylithInt i = 0; i < dim; ++i) {
        g0[0] += a[i_amplitude]*a[i_value];
    } // for
} // g0_timeHistory_vector

/* ----------------------------------------------------------------------
 * Compute boundary condition scalar value using initial and rate terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialRate_scalar(const PylithInt dim,
                                                               const PylithInt numS,
                                                               const PylithInt numA,
                                                               const PylithInt sOff[],
                                                               const PylithInt sOff_x[],
                                                               const PylithScalar s[],
                                                               const PylithScalar s_t[],
                                                               const PylithScalar s_x[],
                                                               const PylithInt aOff[],
                                                               const PylithInt aOff_x[],
                                                               const PylithScalar a[],
                                                               const PylithScalar a_t[],
                                                               const PylithScalar a_x[],
                                                               const PylithReal t,
                                                               const PylithReal x[],
                                                               const PylithReal n[],
                                                               const PylithInt numConstants,
                                                               const PylithScalar constants[],
                                                               PylithScalar g0[]) {
    const PylithInt _numA = 3;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = 0;
    const PylithInt i_rate = 1;
    const PylithInt i_start = 2;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_initial] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_initial] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numARate = 2;
    const PylithInt aOffRate[2] = { aOff[i_rate], aOff[i_start] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rate], a[i_start] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_scalar(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_rate_scalar(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
} // g0_initialRate_scalar

/* ----------------------------------------------------------------------
 * Compute boundary condition vector value using initial and rate terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialRate_vector(const PylithInt dim,
                                                               const PylithInt numS,
                                                               const PylithInt numA,
                                                               const PylithInt sOff[],
                                                               const PylithInt sOff_x[],
                                                               const PylithScalar s[],
                                                               const PylithScalar s_t[],
                                                               const PylithScalar s_x[],
                                                               const PylithInt aOff[],
                                                               const PylithInt aOff_x[],
                                                               const PylithScalar a[],
                                                               const PylithScalar a_t[],
                                                               const PylithScalar a_x[],
                                                               const PylithReal t,
                                                               const PylithReal x[],
                                                               const PylithReal n[],
                                                               const PylithInt numConstants,
                                                               const PylithScalar constants[],
                                                               PylithScalar g0[]) {
    const PylithInt _numA = 3;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = 0;
    const PylithInt i_rate = 1;
    const PylithInt i_start = 2;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_initial] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_initial] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numARate = 2;
    const PylithInt aOffRate[2] = { aOff[i_rate], aOff[i_start] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rate], a[i_start] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_vector(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_rate_vector(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
} // g0_initialRate_vector

/* ----------------------------------------------------------------------
 * Compute boundary condition scalar value using initial and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialTimeHistory_scalar(const PylithInt dim,
                                                                      const PylithInt numS,
                                                                      const PylithInt numA,
                                                                      const PylithInt sOff[],
                                                                      const PylithInt sOff_x[],
                                                                      const PylithScalar s[],
                                                                      const PylithScalar s_t[],
                                                                      const PylithScalar s_x[],
                                                                      const PylithInt aOff[],
                                                                      const PylithInt aOff_x[],
                                                                      const PylithScalar a[],
                                                                      const PylithScalar a_t[],
                                                                      const PylithScalar a_x[],
                                                                      const PylithReal t,
                                                                      const PylithReal x[],
                                                                      const PylithReal n[],
                                                                      const PylithInt numConstants,
                                                                      const PylithScalar constants[],
                                                                      PylithScalar g0[]) {
    const PylithInt _numA = 4;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = 0;
    const PylithInt i_thAmp = 1;
    const PylithInt i_thStart = 2;
    const PylithInt i_thValue = 3;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_initial] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_initial] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_scalar(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_scalar(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_initialTimeHistory_scalar

/* ----------------------------------------------------------------------
 * Compute boundary condition vector value using initial and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialTimeHistory_vector(const PylithInt dim,
                                                                      const PylithInt numS,
                                                                      const PylithInt numA,
                                                                      const PylithInt sOff[],
                                                                      const PylithInt sOff_x[],
                                                                      const PylithScalar s[],
                                                                      const PylithScalar s_t[],
                                                                      const PylithScalar s_x[],
                                                                      const PylithInt aOff[],
                                                                      const PylithInt aOff_x[],
                                                                      const PylithScalar a[],
                                                                      const PylithScalar a_t[],
                                                                      const PylithScalar a_x[],
                                                                      const PylithReal t,
                                                                      const PylithReal x[],
                                                                      const PylithReal n[],
                                                                      const PylithInt numConstants,
                                                                      const PylithScalar constants[],
                                                                      PylithScalar g0[]) {
    const PylithInt _numA = 4;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_initial = 0;
    const PylithInt i_thAmp = 1;
    const PylithInt i_thStart = 2;
    const PylithInt i_thValue = 3;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_initial] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_initial] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_vector(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_vector(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_initialTimeHistory_vector

/* ----------------------------------------------------------------------
 * Compute boundary condition scalar value using rate and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_rateTimeHistory_scalar(const PylithInt dim,
                                                                   const PylithInt numS,
                                                                   const PylithInt numA,
                                                                   const PylithInt sOff[],
                                                                   const PylithInt sOff_x[],
                                                                   const PylithScalar s[],
                                                                   const PylithScalar s_t[],
                                                                   const PylithScalar s_x[],
                                                                   const PylithInt aOff[],
                                                                   const PylithInt aOff_x[],
                                                                   const PylithScalar a[],
                                                                   const PylithScalar a_t[],
                                                                   const PylithScalar a_x[],
                                                                   const PylithReal t,
                                                                   const PylithReal x[],
                                                                   const PylithReal n[],
                                                                   const PylithInt numConstants,
                                                                   const PylithScalar constants[],
                                                                   PylithScalar g0[]) {
    const PylithInt _numA = 5;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_rateAmp = 0;
    const PylithInt i_rateStart = 0;
    const PylithInt i_thAmp = 1;
    const PylithInt i_thStart = 2;
    const PylithInt i_thValue = 3;

    const PylithInt numARate = 1;
    const PylithInt aOffRate[2] = { aOff[i_rateAmp], aOff[i_rateStart] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rateAmp], a[i_rateStart] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_rate_scalar(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_scalar(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_rateTimeHistory_scalar

/* ----------------------------------------------------------------------
 * Compute boundary condition vector value using rate and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_rateTimeHistory_vector(const PylithInt dim,
                                                                   const PylithInt numS,
                                                                   const PylithInt numA,
                                                                   const PylithInt sOff[],
                                                                   const PylithInt sOff_x[],
                                                                   const PylithScalar s[],
                                                                   const PylithScalar s_t[],
                                                                   const PylithScalar s_x[],
                                                                   const PylithInt aOff[],
                                                                   const PylithInt aOff_x[],
                                                                   const PylithScalar a[],
                                                                   const PylithScalar a_t[],
                                                                   const PylithScalar a_x[],
                                                                   const PylithReal t,
                                                                   const PylithReal x[],
                                                                   const PylithReal n[],
                                                                   const PylithInt numConstants,
                                                                   const PylithScalar constants[],
                                                                   PylithScalar g0[]) {
    const PylithInt _numA = 5;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_rateAmp = 0;
    const PylithInt i_rateStart = 0;
    const PylithInt i_thAmp = 1;
    const PylithInt i_thStart = 2;
    const PylithInt i_thValue = 3;

    const PylithInt numARate = 1;
    const PylithInt aOffRate[2] = { aOff[i_rateAmp], aOff[i_rateStart] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rateAmp], a[i_rateStart] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_rate_vector(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_vector(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_rateTimeHistory_vector

/* ----------------------------------------------------------------------
 * Compute boundary condition scalar value using initial, rate ,and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialRateTimeHistory_scalar(const PylithInt dim,
                                                                          const PylithInt numS,
                                                                          const PylithInt numA,
                                                                          const PylithInt sOff[],
                                                                          const PylithInt sOff_x[],
                                                                          const PylithScalar s[],
                                                                          const PylithScalar s_t[],
                                                                          const PylithScalar s_x[],
                                                                          const PylithInt aOff[],
                                                                          const PylithInt aOff_x[],
                                                                          const PylithScalar a[],
                                                                          const PylithScalar a_t[],
                                                                          const PylithScalar a_x[],
                                                                          const PylithReal t,
                                                                          const PylithReal x[],
                                                                          const PylithReal n[],
                                                                          const PylithInt numConstants,
                                                                          const PylithScalar constants[],
                                                                          PylithScalar g0[]) {
    const PylithInt _numA = 6;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_valueAmp = 0;
    const PylithInt i_rateAmp = 1;
    const PylithInt i_rateStart = 2;
    const PylithInt i_thAmp = 3;
    const PylithInt i_thStart = 4;
    const PylithInt i_thValue = 5;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_valueAmp] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_valueAmp] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numARate = 1;
    const PylithInt aOffRate[2] = { aOff[i_rateAmp], aOff[i_rateStart] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rateAmp], a[i_rateStart] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_scalar(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_rate_scalar(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_scalar(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_initialRateTimeHistory_scalar


/* ----------------------------------------------------------------------
 * Compute boundary condition vector value using initial, rate, and time history terms.
 */
void
pylith::fekernels::NeumannTimeDependent::g0_initialRateTimeHistory_vector(const PylithInt dim,
                                                                          const PylithInt numS,
                                                                          const PylithInt numA,
                                                                          const PylithInt sOff[],
                                                                          const PylithInt sOff_x[],
                                                                          const PylithScalar s[],
                                                                          const PylithScalar s_t[],
                                                                          const PylithScalar s_x[],
                                                                          const PylithInt aOff[],
                                                                          const PylithInt aOff_x[],
                                                                          const PylithScalar a[],
                                                                          const PylithScalar a_t[],
                                                                          const PylithScalar a_x[],
                                                                          const PylithReal t,
                                                                          const PylithReal x[],
                                                                          const PylithReal n[],
                                                                          const PylithInt numConstants,
                                                                          const PylithScalar constants[],
                                                                          PylithScalar g0[]) {
    const PylithInt _numA = 6;
    assert(_numA == numA);
    assert(aOff);
    assert(a);

    const PylithInt i_valueAmp = 0;
    const PylithInt i_rateAmp = 1;
    const PylithInt i_rateStart = 2;
    const PylithInt i_thAmp = 3;
    const PylithInt i_thStart = 4;
    const PylithInt i_thValue = 5;

    const PylithInt numAInitial = 1;
    const PylithInt aOffInitial[1] = { aOff[i_valueAmp] };
    const PylithInt* aOffInitial_x = NULL;
    const PylithScalar aInitial[1] = { a[i_valueAmp] };
    const PylithScalar* aInitial_t = NULL;
    const PylithScalar* aInitial_x = NULL;

    const PylithInt numARate = 1;
    const PylithInt aOffRate[2] = { aOff[i_rateAmp], aOff[i_rateStart] };
    const PylithInt* aOffRate_x = NULL;
    const PylithScalar aRate[2] = { a[i_rateAmp], a[i_rateStart] };
    const PylithScalar* aRate_t = NULL;
    const PylithScalar* aRate_x = NULL;

    const PylithInt numATimeHistory = 3;
    const PylithInt aOffTimeHistory[3] = { aOff[i_thAmp], aOff[i_thStart], aOff[i_thValue] };
    const PylithInt* aOffTimeHistory_x = NULL;
    const PylithScalar aTimeHistory[3] = { a[i_thAmp], a[i_thStart], a[i_thValue] };
    const PylithScalar* aTimeHistory_t = NULL;
    const PylithScalar* aTimeHistory_x = NULL;

    pylith::fekernels::NeumannTimeDependent::g0_initial_vector(dim, numS, numAInitial, sOff, sOff_x, s, s_t, s_x, aOffInitial, aOffInitial_x, aInitial, aInitial_t, aInitial_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_rate_vector(dim, numS, numARate, sOff, sOff_x, s, s_t, s_x, aOffRate, aOffRate_x, aRate, aRate_t, aRate_x, t, x, n, numConstants, constants, g0);
    pylith::fekernels::NeumannTimeDependent::g0_timeHistory_vector(dim, numS, numATimeHistory, sOff, sOff_x, s, s_t, s_x, aOffTimeHistory, aOffTimeHistory_x, aTimeHistory, aTimeHistory_t, aTimeHistory_x, t, x, n, numConstants, constants,
                                                                   g0);
} // g0_initialRateTimeHistory_vector


// End of file