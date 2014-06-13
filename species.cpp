#include "species.h"


Species::Species(int prodCount, float *prodConc, int enzyCount, float *enzyConc):
    pCount(prodCount), eCount(enzyCount), pConc(prodConc), eConc(enzyConc)
{

}
//Species::Species(){}

std::string Species::getString()
{
    std::stringstream ss;
    ss << pCount << " : ";
    for(int i = 0 ; i < pCount ; i ++)
        ss << pConc[i] << ", ";
    ss << eCount << " : ";
    for(int i = 0 ; i < eCount ; i ++)
        ss << eConc[i] << ", ";
    ss<<std::endl;
    return ss.str();
}


Species Species::operator *(const int factor)
{
    Species *s = new Species(*this);
    for(int i = 0 ; i < this->pCount ; i++)
    {
        s->pConc[i] *= factor;
    }
    for(int i = 0 ; i < this->eCount ; i++)
    {
        s->eConc[i] *= factor;
    }
    return (*s);
}

void Species::operator +=(const Species & rhs)
{
    for(int i = 0 ; i < this->pCount ; i++)
    {
        pConc[i] += rhs.pConc[i];
    }
    for(int i = 0 ; i < this->eCount ; i++)
    {
        eConc[i] += rhs.eConc[i];
    }
}

void Species::operator=(const Species & rhs)
{
#ifdef DEBUG
    std::cout<<"Toi ! "<<std::endl;
#endif
    this->pConc = new float[rhs.pCount];
    this->eConc = new float[rhs.eCount];

    for(int i = 0 ; i < rhs.pCount;i++)
        pConc[i] = rhs.pConc[i];
    for(int i = 0 ; i < rhs.eCount ; i ++)
        eConc[i] = rhs.eConc[i];

    this->pCount = rhs.pCount;
    this->eCount = rhs.eCount;


}

Species::Species(const Species& rhs)
{
    this->pConc = new float[rhs.pCount];
    this->eConc = new float[rhs.eCount];

    for(int i = 0 ; i < rhs.pCount;i++)
        pConc[i] = rhs.pConc[i];
    for(int i = 0 ; i < rhs.eCount ; i ++)
        eConc[i] = rhs.eConc[i];
}

std::ostream &operator <<(std::ostream &os, const Species &s)
{
    return os; // << s.
}


float Species::getProductionConcentration(int p)
{
    if(p < pCount)
    {
        return pConc[p];
    }
}

std::ofstream &Species::operator <<(std::ofstream &os)
{
    os << "Produit : "<<this->pCount <<std::endl;
    os << this->pConc[0];
    for(int i = 1 ; i < this->pCount ; i++)
    {
        os << " ; " << this->pConc[i];
    }
    os<<std::endl;
    return os;
}
