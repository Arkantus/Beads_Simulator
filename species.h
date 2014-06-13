#ifndef SPECIES_H
#define SPECIES_H

#include<string>
#include<sstream>
#include<fstream>

#ifdef DEBUG
    #include <iostream>
#endif

class Species
{
public:
    //Species();
    Species(int prodCount, float * prodConc, int enzyCount, float * enzyConc);
    std::string getString();
    Species operator *(const int);
    void operator +=(const Species&);
    void operator =(const Species&);
    Species(const Species& rhs);
    float getProductionConcentration(int);
    std::ofstream& operator <<(std::ofstream &os);
private:
    int pCount, eCount;
    float * pConc, *eConc;
};

std::ostream& operator << (std::ostream& os, const Species& s );


enum class Componant{
    Null
};

enum class Enzyme{
    E1, E2, E3, E4, E5, E6, E7, E8, E9, E10
};

enum class Product{
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};




#endif // SPECIES_H
