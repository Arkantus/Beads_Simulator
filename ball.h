#ifndef BALL_H
#define BALL_H

#include "reaction.h"
#include "species.h"
#include <cmath>
#include "gsl/gsl_odeiv.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include "odes.h"
#include <cstdlib>
#include <ostream>
#include <boost/math/special_functions.hpp>

#ifdef DEBUG
    #include <iostream>
#endif

class Ball
{
private:
    float mass;
    std::vector<Reaction> react;
    bool init;
    const gsl_odeiv_step_type * stepper = gsl_odeiv_step_rkf45;
    gsl_odeiv_step * s;
    gsl_odeiv_control * c;
    gsl_odeiv_evolve * e;
    gsl_odeiv_system sys;
    //gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,1e-6, 1e-6, 0.0);
    size_t dim;
    static int index_max;
    int index;


public:
    float * coord;
    int reactionNumbers;
    Species * species;
    Species * speciesPrevious;

    Species computeSprayed();

    Ball();
    Ball(Species*, Reaction*, int, float*);
    Ball(Species*, std::vector<Reaction> init_react, float*, Species*);

    Ball(const Ball&);
    Ball& operator=(const Ball&);

    Species getSpecies() const;

    friend float d(const Ball& b1, const Ball& b2);
    friend int deriv(double t, const double y[], double f[],void *params);

    static float mcDonald(float r, float a);

    void move();
    void compute(float);

    ~Ball();

    enum logLevel{nothing=0,concentration=10,reaction=100};
    void log(int, std::ostream& os); //enum class avec differnt niveaux !



};

#endif // BALL_H
