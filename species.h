#ifndef SPECIES_H
#define SPECIES_H

#include<string>
#include<sstream>
#include<fstream>


enum class Componant{
    Null
};

enum class Enzyme{
    E0= 0, E1, E2, E3, E4, E5, E6, E7, E8, E9
};

enum class Product{
    A = 0,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};

class Species
{
public:
    Species(int prodCount, double *prodConc, int enzyCount, double *enzyConc);
    Species(int prodCount, float * prodConc, int enzyCount, float * enzyConc);
    Species();
    Species operator *(const float);
    void operator +=(const Species&);
    void operator =(const Species&);
    Species(const Species& rhs);
    float getProductionConcentration(int)const;
    float getProductConcentration(Product p) const;
    void operator*=(const float);
    const int ProductCount();
    void update(float*);
    void update(const double *&);
    void updateBang(double *);
    friend Species operator*(float factor, Species rhs);
    friend std::ostream& operator << (std::ostream& os, const Species& s );
    ~Species();
    float * pConc, *eConc;
    void reset();


private:
    int pCount, eCount;
};


#endif // SPECIES_H
