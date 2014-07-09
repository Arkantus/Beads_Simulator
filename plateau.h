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
    plateau(std::vector<Ball> *p);
    void init (int dx, int dy);
    std::vector<Ball>* balls;
};

#endif // PLATEAU_H
