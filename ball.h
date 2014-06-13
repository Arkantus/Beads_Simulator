#ifndef BALL_H
#define BALL_H

#include "reaction.h"
#include "species.h"
#include <cmath>
#include "gsl/gsl_odeiv.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include "odes.h"
#include <cstdlib>

#ifdef DEBUG
    #include <iostream>
#endif

class Ball
{
private:
    Reaction * reactions;
    int reactionNumbers;
    float * coord;
    //constexpr
    gsl_odeiv_step_type * stepper;// = gsl_odeiv_step_bsimp;
    gsl_odeiv_step * s;
    gsl_odeiv_control * c;
    gsl_odeiv_evolve * e;
    gsl_odeiv_system sys;


public:
    Ball();
    Ball(const Ball&);
    float x();
    float y();
    Species* species;
    friend float d(const Ball& b1, const Ball& b2);
    void move();
    Ball(Species*, Reaction*, int, float*);
    void compute(int n_steps);
    Ball& operator=(const Ball&);
    Species getSpecies();
    ~Ball();

};

//int func2 (double t, const double y[], double f[],void *params);
//int jac2 (double t, const double y[], double *dfdy, double dfdt[], void *params);



#endif // BALL_H
