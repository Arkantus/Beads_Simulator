#include "species.h"


Species::Species(int prodCount, float *prodConc, int enzyCount, float *enzyConc):
    pCount(prodCount), eCount(enzyCount)
{
    pConc = new float[pCount];
    for(int i = 0 ; i < pCount ; i ++ )
        pConc[i] = prodConc[i];
    eConc = new float[eCount];
    for(int i = 0 ; i < eCount ; i ++ )
        eConc[i] = enzyConc[i];

}


Species::Species(int prodCount, double *prodConc, int enzyCount, double *enzyConc):
    pCount(prodCount), eCount(enzyCount)
{
    pConc = new float[pCount];
    for(int i = 0 ; i < pCount ; i ++ )
        pConc[i] = (float)prodConc[i];
    eConc = new float[eCount];
    for(int i = 0 ; i < eCount ; i ++ )
        eConc[i] = (float)enzyConc[i];

}

Species::Species()
{
    eConc = new float[0];
    pConc = new float[0];

}
const int Species::ProductCount()
{
    return pCount;
}

void Species::update(float * c)
{
    for(int i = 0 ; i < this->pCount ; i ++)
        pConc[i]= c[i];
}

void Species::update(const double *& c)
{
    for(int i = 0 ; i < this->pCount ; i ++)
        pConc[i]= c[i];
}

void Species::updateBang(double * c)
{
    for(int i = 0 ; i < this->pCount ; i ++)
        pConc[i] +=(float) c[i];
}

Species Species::operator *(const float factor)
{
    Species s = (*this);
    for(int i = 0 ; i < this->pCount ; i++)
    {
        s.pConc[i] *= factor;
    }
    for(int i = 0 ; i < this->eCount ; i++)
    {
        s.eConc[i] *= factor;
    }
    return (s);
}

Species::~Species()
{
    delete[] pConc;
    delete[] eConc;
}

void Species::operator +=(const Species & rhs)
{
    for(int i = 0 ; i < rhs.pCount ; i++)
    {
        pConc[i] += rhs.pConc[i];
    }
    for(int i = 0 ; i < rhs.eCount ; i++)
    {
        eConc[i] += rhs.eConc[i];
    }
}

void Species::operator *=(const float rhs)
{
    for(int i = 0 ; i < this->pCount ; i++)
        pConc[i] *= rhs;
}

void Species::operator=(const Species & rhs)
{
    this->pCount = rhs.pCount;
    this->eCount = rhs.eCount;

    this->pConc = new float[rhs.pCount];
    this->eConc = new float[rhs.eCount];

    for(int i = 0 ; i < rhs.pCount;i++)
        pConc[i] = rhs.pConc[i];
    for(int i = 0 ; i < rhs.eCount ; i ++)
        eConc[i] = rhs.eConc[i];
}

Species::Species(const Species& rhs)
{
    this->pCount = rhs.pCount;
    this->eCount = rhs.eCount;

    this->pConc = new float[rhs.pCount];
    this->eConc = new float[rhs.eCount];

    for(int i = 0 ; i < rhs.pCount;i++)
        pConc[i] = rhs.pConc[i];
    for(int i = 0 ; i < rhs.eCount ; i ++)
        eConc[i] = rhs.eConc[i];
}

std::ostream &operator <<(std::ostream &os, const Species &s)
{
    os << s.pConc[0];
    for(int i = 1 ; i < s.pCount ; i++)
    {
        os << " ; " << s.pConc[i];
    }
    return os;
}


float Species::getProductionConcentration(int p) const
{
    return pConc[p];
}

float Species::getProductConcentration(Product p) const
{
    return pConc[(int)p];
}

Species operator*(float factor, Species rhs)
{
    Species s = rhs;
    for(int i = 0 ; i < rhs.pCount ; i++)
    {
        s.pConc[i] *= factor;
    }
    for(int i = 0 ; i < rhs.eCount ; i++)
    {
        s.eConc[i] *= factor;
    }
    return (s);
}
