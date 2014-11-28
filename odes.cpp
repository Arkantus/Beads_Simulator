#include "odes.h"

int deriv(double t, const double y[], double f[], void *params)
{
    Ball b = *((Ball*)(params));
    Species s(*b.species);
    //plutôt avec y pour la vitesse?
    for(int i = 0 ; i < b.species->ProductCount() ; i++) f[i] = 0.0;

    b.species->update(y);

    for (int j = 0 ; j < b.react.size() ; j ++)
    {
        float rateLR = b.react[j].kp, rateRL = b.react[j].km;

        for(int i = 0 ; i < b.react[j].right->size() ; i ++)
            rateRL *= b.species->getProductConcentration(b.react[j].right->at(i));

        for(int i = 0 ; i < b.react[j].left->size() ; i ++)
            rateLR *= b.species->getProductConcentration(b.react[j].left->at(i));


        #pragma ivdep
        for(int i = 0 ; i < b.react[j].right->size() ; i ++)
        {
            f[(int)b.react[j].right->at(i)] += rateLR;
            f[(int)b.react[j].right->at(i)] -= rateRL;
          //  f[(int)b.react[j].right->at(i)] = (f[(int)b.react[j].right->at(i)] * b.react[j].kp)/(1+f[(int)b.react[j].right->at(i)]);
        }


        #pragma ivdep
        for(int i = 0 ; i < b.react[j].left->size() ; i ++)
        {
            f[(int)b.react[j].left->at(i)] += rateRL;
            f[(int)b.react[j].left->at(i)] -= rateLR;
           // f[(int)b.react[j].left->at(i)] = (f[(int)b.react[j].left->at(i)] * b.react[j].km )/(1+f[(int)b.react[j].left->at(i)]);
        }

    }

    return GSL_SUCCESS;
}


void deriv(double f[], void *params)
{
    Ball b = *((Ball*)(params));

    for(int i = 0 ; i < b.species->ProductCount() ; i++) f[i] = 0.0;

    for (int j = 0 ; j < b.react.size() ; j ++)
    {
        float rateLR = b.react[j].kp;

        for(int i = 0 ; i < b.react[j].left->size() ; i ++)
            rateLR *= b.species->getProductConcentration(b.react[j].left->at(i));

        #pragma ivdep
        for(int i = 0 ; i < b.react[j].right->size() ; i ++)
        {
            f[(int)b.react[j].right->at(i)] += rateLR;
        }
    }
}


/*void deriv(double f[],float timestep, void *params)
{
    //timestep <= 1
    Ball b = *((Ball*)(params));

    for(int i = 0 ; i < b.species->ProductCount() ; i++) f[i] = 0.0;

    for (int j = 0 ; j < b.react.size() ; j ++)
    {
        float rateLR = b.react[j].kp;

        for(int i = 0 ; i < b.react[j].left->size() ; i ++)
            rateLR *= b.species->getProductConcentration(b.react[j].left->at(i));

        #pragma ivdep
        for(int i = 0 ; i < b.react[j].right->size() ; i ++)
        {
            f[(int)b.react[j].right->at(i)] += rateLR;
        }
    }    
}

/*int jaco(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    //Seul la premiere colonne est remplie !
}*/
