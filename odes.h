#ifndef ODES_H
#define ODES_H

#include "gsl/gsl_odeiv.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>

#ifdef DEBUG
    int func (double t, const double y[], double f[],void *params);
    int jac (double t, const double y[], double *dfdy, double dfdt[], void *params);
#endif

#endif // ODES_H
