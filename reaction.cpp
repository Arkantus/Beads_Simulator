#include "reaction.h"


Reaction::Reaction(): Reaction::Reaction(std::string("Default"))
{

}
Reaction::Reaction(std::string chaine)
{
    //for push_back
#ifdef DEBUG
    left = new std::vector<Product>(2);
    right = new std::vector<Product>(1);
    E = Enzyme::E1;
    left->push_back(Product::A);
    left->push_back(Product::B);
    right->push_back(Product::C);
#else
    std::string buf;
    std:: stringstream ss(chaine);
    std::vector<std::string> tokens;
    while(ss >> buf)
        tokens.push_back(buf);
    for(std::string s : tokens)
    {
        if(s.length() == 1)
        {//product

        }
        else if(s.length() == 2)
        {//Enzyme

        }
        else
        {
            // ==> or <== or <==>
        }
    }
#endif
}
