#include "reaction.h"


Reaction::Reaction()
{
    left = new std::vector<Product>(2);
    right = new std::vector<Product>(2);
    E = static_cast<Enzyme>(0);
    km = 0;
    kp = 0;
}
Reaction::Reaction(std::string chaine, float _kp, float _km)
{
    km = _km;
    kp = _kp;
    left = new std::vector<Product>();
    right = new std::vector<Product>();
    std::vector<Product> * reac;
    reac = left;
    std::string buf;
    std:: stringstream ss(chaine);
    std::vector<std::string> tokens;
    while(ss >> buf)
        tokens.push_back(buf);
    for(std::string s : tokens)
    {
        if(s.length() == 1 && std::isalpha(s[0])){
            reac->push_back(static_cast<Product>((int)s[0]-'A')); //degeu (Award level) !
            std::clog<<s<<"  " <<((int)s[0]-'A') <<std::endl;
        }

        else if(s.length() > 1 && s[0] == 'E')
            E = static_cast<Enzyme>(s[1]);

        else
            if(s[0] == '=') // ou s[1] pas de jaloux
                reac = right;
    }
    left->shrink_to_fit();
    right->shrink_to_fit();
}

Reaction::Reaction(const Reaction & rhs)
{
    this->E = rhs.E;
    this->km = rhs.km;
    this->kp = rhs.kp;
    this->left = new std::vector<Product>(*rhs.left);
    this->right = new std::vector<Product>(*rhs.right);
}

Reaction::~Reaction()
{
    delete left;
    delete right;
}

std::ostream& operator <<(std::ostream &of, const Reaction &r)
{
    for(Product p : *r.left)
        of << (char)((int)p+'A')<<" ";
    of << "==> ";
    for(Product p : *r.right)
        of << (char)((int)p+'A') << " ";
    of << "\t[k_p : " << r.kp <<"\t"<< " k_m : "<<r.km<<"]";

    return of;
}
