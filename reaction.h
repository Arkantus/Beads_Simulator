#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <string>
#include <sstream>
#include <locale>
#include <ostream>
#include "species.h"

#ifdef DEBUG

    #include<iostream>

#endif

class Reaction
{
public:
    Reaction();
    Reaction(std::string chaine, float _kp, float _km);
    Reaction(const Reaction&);

    friend std::ostream &operator << (std::ostream& os, const Reaction& r );

    std::vector<Product> *right;
    std::vector<Product> *left;
    Enzyme E;
    float kp;
    float km;

    ~Reaction();
};



#endif // REACTION_H
