#include "ball.h"

Ball::Ball(Species* init_s, Reaction * init_r, int num_r, float * pos)
{
    this->species = init_s;
    this->reactions = init_r;
    this->reactionNumbers = num_r;
    this->coord = new float[2];
    this->coord[0] = pos[0];
    this->coord[1] = pos[1];

    s = gsl_odeiv_step_alloc (stepper, 2);
    c = gsl_odeiv_control_y_new (1e-6, 0.0);
    e = gsl_odeiv_evolve_alloc (2);

    std::cout<<this->coord[0]<<std::endl;

    double mu = 10;
    sys.dimension = 2;
    sys.function = func;
    sys.jacobian = jac;
    sys.params = (void*)&mu;
}

float d(const Ball &b1, const Ball &b2)
{
    float x = b1.coord[0] - b2.coord[0];
    float y = b1.coord[1] - b2.coord[1];
    return std::hypot(x,y);
}

void Ball::compute(int n_steps)
{
#ifdef DEBUG
    //std::cout<<"LALALAL : "<<this->coord[1]<<std::endl;
    std::cout<<"LALALA"<<this->sys.dimension<<std::endl;
    double t = 0.0, t1 = 5.0;
    double h = 1e-6;
    double y[2] = { 1.0, 0.0 };

    while (t < t1)
      {

       // int status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, t1, &h, y);

        //if (status != GSL_SUCCESS)
          //  break;

        printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
      }

#endif
}


Ball::~Ball()
{
    static int i = 0;
    std::cout << "Destructor je suis appelé pour là " << ++i <<"ieme fois"<<std::endl;

    gsl_odeiv_evolve_free (e);
    gsl_odeiv_control_free (c);
    gsl_odeiv_step_free (s);
}

void Ball::move()
{
    for(int i = 0 ; i < 2 ; i++) //Unroll dumb loop (performance wise) but 3D balls? Oh YEAH
        //Ou alors on décide à la compilation avec un if
        do
        {
            this->coord[i] += (((float)(rand()/RAND_MAX))*2.f)-1.f; //En fait il faut bouger beaucoup moins que ça !
        }
        while(this->coord[i] >= 1 || this->coord[i] <= 0 );
}
