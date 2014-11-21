#include"misc.hpp"


float mixingCoeff(const float d)
{
    return exp(-d*sqrt(Configuration::k_decay/Configuration::D_chemicals))/(2*sqrt(Configuration::D_chemicals*Configuration::k_decay));
}

float expD(float r)
{
    return 2*sqrt(Configuration::k_decay*Configuration::D_chemicals)*exp(-r*sqrt(Configuration::k_decay/Configuration::D_chemicals));
}

float mcDonald(float r) //Config avec les params k_decay et k
{
    if(r == 0)
        r = Configuration::beadSize;
    float D=Configuration::D_chemicals, k=Configuration::k_decay;
    return (1.f/(2*M_PI*D)*boost::math::cyl_bessel_k(0,r*sqrt(k/D)));
    //return expD(r);
}


