#ifndef ODES_H
#define ODES_H

#include "gsl/gsl_odeiv.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <algorithm>
#include "ball.h"

int deriv(double t, const double y[], double f[], void *params);
void deriv(double f[], void *params);

//int jaco(double t, const double y[], double *dfdy, double dfdt[], void *params);

#endif // ODES_H
