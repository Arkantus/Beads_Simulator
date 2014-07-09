#include "ball.h"

int Ball::index_max = 0;

Ball::Ball(Species* init_s, std::vector<Reaction> init_react, float * pos, Species *tbS)
{
    index = index_max;
    index_max++;

    init = true;
    this->species = new Species(*init_s);
    this->speciesPrevious = new Species(*tbS);
    this->react = std::vector<Reaction>(init_react);
    this->coord = new float[2];
    this->coord[0] = pos[0];
    this->coord[1] = pos[1];

    dim = species->ProductCount();

    s = gsl_odeiv_step_alloc (stepper, dim);
    c = gsl_odeiv_control_y_new (1e-6, 0.0);
    e = gsl_odeiv_evolve_alloc (dim);

    sys.dimension = species->ProductCount();
    sys.function = deriv;
    sys.jacobian = nullptr;
    sys.params = (void*)this;
}

Ball::Ball(const Ball& rhs)
{
    init = true;

    this->species = new Species(*rhs.species);
    this->react = std::vector<Reaction>(rhs.react);
    index = rhs.index;
    this->speciesPrevious = new Species(*rhs.speciesPrevious);




    this->coord = new float[2];
    this->coord[0] = rhs.coord[0];
    this->coord[1] = rhs.coord[1];
    //this->d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_bsimp, 1e-6, 1e-6, 0.0);

    s = gsl_odeiv_step_alloc (stepper,species->ProductCount());
    c = gsl_odeiv_control_y_new (1e-6, 0.0);
    e = gsl_odeiv_evolve_alloc(species->ProductCount());

    sys.dimension = species->ProductCount();
    sys.function = deriv;
    sys.jacobian = nullptr;
    sys.params = (void*)this;
}

Ball& Ball::operator=(const Ball& rhs)
{
    init = true;

    this->species = new Species(*rhs.species);
    this->react = std::vector<Reaction>(rhs.react);
    this->speciesPrevious = new Species(*rhs.speciesPrevious);
    index = rhs.index;

    this->coord = new float[2];
    this->coord[0] = rhs.coord[0];
    this->coord[1] = rhs.coord[1];
    //this->d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_bsimp, 1e-6, 1e-6, 0.0);

    s = gsl_odeiv_step_alloc (stepper, rhs.dim);
    c = gsl_odeiv_control_y_new (1e-6, 0.0);
    e = gsl_odeiv_evolve_alloc (rhs.dim);

    sys.dimension = species->ProductCount();;
    sys.function = deriv;
    sys.jacobian = nullptr;
    sys.params = (void*)this;
}

Species Ball::computeSprayed()
{
    int np = species->ProductCount();

    float * products = new float[np];

    for(int i = 0 ; i < np ; i ++)
    {
        products[i] = species->getProductionConcentration(i) - speciesPrevious->getProductionConcentration(i);
        if(products[i] < 0)
            products[i] = 0;
    }

    Species s(np, products, 0, products);
    delete[] products;
    return s;
}

Ball::Ball()
{
    init = false;
}


void Ball::log(int lvl, std::ostream &os)
{

    if((int)lvl & 0xA)
    {
        os << "Ball     : "<<this->index <<std::endl;
        os << "coord    : "<< this->coord[0] << ", " <<this->coord[1] <<std::endl;
        os << "in       : " ;
        os << *species <<std::endl;
        os << "out      : ";
        os << computeSprayed() <<std::endl;

    }
    if((int)lvl & 0x64)
    {
        os << "Reaction : "<<std::endl;
        for(Reaction k : react)
            os <<"           "<< k << std::endl;
    }

    os << std::endl;

}

void Ball::compute(float elapsed_time)
{
    double t = 0.0;
    double h = 1e-3;
    double * yn = new double[this->species->ProductCount()];
    int nPB = species->ProductCount();
    *speciesPrevious = *species;

    for(int i = 0 ; i < this->species->ProductCount() ; i ++)
        yn[i] = this->species->getProductionConcentration(i);

    while (t < elapsed_time)
    {
        gsl_odeiv_evolve_apply (e, c, s, &sys, &t, elapsed_time, &h, yn);
    }

    delete this->species;
    this->species = new Species(nPB,yn,0,yn);
    delete[] yn;
}

void Ball::move()
{
    for(int i = 0 ; i < 2 ; i++) //Unroll dumb loop (performance wise) but 3D balls?
    {
        float mvt = (float)rand() / RAND_MAX; //O..1
        mvt *= 2;       // 0..2
        mvt -= 1;       // -1 .. 1
        mvt *= 1E-3;    //-.01 .. 01

        this->coord[i] += mvt;
#pragma GCC message "Marche pas partout TODO"
        if(this->coord[i]>=1 || this->coord<= 0)
        {
            this->coord[i]-=2*mvt;
        }
    }
}

float Ball::mcDonald(float r, float a) //Config avec les params Decay et k
{
    float D, k;
    return (a/(2*M_PI*D)*boost::math::cyl_bessel_k(0,r*sqrt(k/D)));
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
        gsl_odeiv_evolve_free (e);
        gsl_odeiv_control_free (c);
        gsl_odeiv_step_free (s);
        if(species)
        delete species;
    }
    //gsl_odeiv2_driver_free (d);
}

