#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ball.h"
#include <string>
#include <vector>
#include <fstream>
#include <QtCore/QSettings>
#include <cstdlib>
#include <map>
#include<ctime>

class Configuration
{
public:
    Configuration();
    void setParallel(int nb, int nbMax = -1);
    void ReadConf(std::string file = "/home/marc/workspace/synthetic_balls/params.cnf");
    void createDefaultWorld(int);
    void convert();
    int numBalls();

    static const bool gBrownian = true;

    std::map<std::string,float> mp;

    static float threshold;
    static float D_chemicals;        //µm².min**-1
    static float k_decay;    //min**-1
    static float D_beads;
    //static float size_x;
    //static float size_y;
    static float beadSize;

    static int totalSteps;

    std::vector<Ball>* tbr;

    //QSettings settings;

    std::vector<Ball> *getBalls();
};



#endif // CONFIGURATION_H
