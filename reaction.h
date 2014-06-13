#ifndef REACTION_H
#define REACTION_H

#include <vector>
#include <string>
#include <sstream>
#include "species.h"

class Reaction
{
public:
    Reaction();
    Reaction(std::string chaine);
private:
    std::vector<Product> *right;
    std::vector<Product> *left;
    Enzyme E;
    float kp;
    float km;
};

#endif // REACTION_H
