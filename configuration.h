#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ball.h"
#include <string>
#include <vector>
#include <fstream>
#include <QtCore/QSettings>

class Configuration
{
public:
    Configuration();
    void setParallel(int nb, int nbMax = -1);
    void ReadConf(std::string file);
    int numBalls();

    static const bool gBrownian = true;

    static float threshold;
    static float D_chemicals;        //µm².min**-1
    static float decay;    //min**-1
    static float D_beads;

    int totalSteps;

    std::vector<Ball>* tbr;

    //QSettings settings;

    std::vector<Ball> *getBalls();


   // ~Configuration();

};

#endif // CONFIGURATION_H
