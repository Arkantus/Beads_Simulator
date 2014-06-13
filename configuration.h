#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ball.h"
#include <string>
#include <vector>
#include <fstream>
//#include <QtCore/QSettings>

class Configuration
{
public:
    Configuration();
    void setParallel(int nb, int nbMax = -1);
    void ReadConf(std::string file);
    std::vector<Ball*>* tbr;

    float threshold;

    //QSettings settings;

    std::vector<Ball *> *getBalls();

    int totalSteps;
    int reactSteps;

    int density_x;
    int density_y;

    float** diffusionCoeff;
    int diffusionNode;
};

#endif // CONFIGURATION_H
