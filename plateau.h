#ifndef PLATEAU_H
#define PLATEAU_H

#include"ball.h"
#include"species.h"
#include<vector>

#ifdef DEBUG

    #include<iostream>

#endif

class plateau
{
private:

public:
    plateau(std::vector<Ball*> *p);
    void init (int dx, int dy);
    std::vector<Ball*>* balls;
    void communicate();

    //std::vector<std::vector<Species*>> surface;

};

#endif // PLATEAU_H
