#include"misc.hpp"


float mixingCoeff(const float d)
{
    return exp(-d*sqrt(Configuration::decay/Configuration::D_chemicals))/(2*sqrt(Configuration::D_chemicals*Configuration::decay));
}

float mcDonald(const float r) //Config avec les params Decay et k
{
    if(r == 0)
        return 1;
    float D=Configuration::D_chemicals, k=Configuration::decay;
    return (1.f/(2*M_PI*D)*boost::math::cyl_bessel_k(0,r*sqrt(k/D)));
}
