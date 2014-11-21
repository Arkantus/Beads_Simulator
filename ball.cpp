#include "ball.h"

int Ball::index_max = 0;

Ball::Ball(Species* init_s, std::vector<Reaction> init_react, float * pos)
{
    index = index_max;
    index_max++;

    init = true;
    this->species = new Species(*init_s);
    this->react = std::vector<Reaction>(init_react);
    this->coord = new float[2];
    this->coord[0] = pos[0];
    this->coord[1] = pos[1];

    productedSpecies = Species();

    dim = species->ProductCount();

    a = new float[dim];

    init_integrator();
}

Ball::Ball(const Ball& rhs)
{
    init = true;

    this->species = new Species(*rhs.species);
    this->react = std::vector<Reaction>(rhs.react);
    index = rhs.index;

    dim = rhs.dim;

    productedSpecies = Species(rhs.productedSpecies);

    a = new float[rhs.dim];
    for(int i = 0 ; i < rhs.dim ; i ++)
        this->a[i] = rhs.a[i];

    this->coord = new float[2];
    this->coord[0] = rhs.coord[0];
    this->coord[1] = rhs.coord[1];

    init_integrator();
}

Ball& Ball::operator=(const Ball& rhs)
{
    init = true;

    this->species = new Species(*rhs.species);
    this->react = std::vector<Reaction>(rhs.react);
    index = rhs.index;

    productedSpecies = Species(rhs.productedSpecies);

    dim = rhs.dim;

    a = new float[rhs.dim];
    for(int i = 0 ; i < rhs.dim ; i ++)
        this->a[i] = rhs.a[i];

    this->coord = new float[2];
    this->coord[0] = rhs.coord[0];
    this->coord[1] = rhs.coord[1];

    init_integrator();
}

void Ball::init_integrator()
{
    //this->c =
    s = gsl_odeiv_step_alloc(stepper,dim);
    c = gsl_odeiv_control_y_new(1e-6,0.0);
    e = gsl_odeiv_evolve_alloc(dim);

}

Ball::Ball()
{
    init = false;
}


void Ball::log(int lvl, std::ostream &os)
{
    std::stringstream ss;

    if((int)lvl & 0xA)
    {
        ss << "Ball     : "<<this->index <<std::endl;
        ss << "coord    : "<< this->coord[0] << ", " <<this->coord[1] <<std::endl;
        ss << "in       : " ;
        ss << *species <<std::endl;
        ss << "out      : ";
        ss << productedSpecies <<std::endl;

    }
    if((int)lvl & 0x64)
    {
        ss << "Reaction : "<<std::endl;
        for(Reaction k : react)
            ss <<"           "<< k << std::endl;
    }

    os << ss.str() << std::endl;

}

void Ball::compute(float elapsed_time)
{
    double * a = new double[this->species->ProductCount()];
    deriv(a,this);
    productedSpecies = Species(species->ProductCount(),a,0,a);
    delete[] a;
}


void Ball::move()
{
    for(int i = 0 ; i < 2 ; i++) //Unroll dumb loop (performance wise) but 3D balls?
    {
        float mvt = (float)rand() / RAND_MAX; //O..1
        mvt *= 2;       // 0..2
        mvt -= 1;       // -1 .. 1
        mvt *= 1E-1;    //-.01 .. 01

        this->coord[i] += mvt;
#pragma GCC message "Marche pas partout TODO"
        if(this->coord[i]>=1 || this->coord<= 0)
        {
            this->coord[i]-=2*mvt;
        }
    }
}




float d(const Ball &b1, const Ball &b2)
{
    float x = b1.coord[0] - b2.coord[0];
    float y = b1.coord[1] - b2.coord[1];
    return std::hypot(x,y);
}

Ball::~Ball()
{
    if(init)
    {
        delete[] coord;
        if(species)
        delete species;
        delete[] a;
        gsl_odeiv_evolve_free(e);
        gsl_odeiv_control_free(c);
        gsl_odeiv_step_free(s);
    }
}

