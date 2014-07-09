#include <iostream>
#include <chrono>
#include <ctime>
#include"configuration.h"
#include"plateau.h"
#include"ball.h"
#include"display.h"
#include"omp.h"

using namespace std;

float mixingCoeff(const float d, const Configuration c)
{
    return exp(-d*sqrt(c.decay/c.D_chemicals))/(2*sqrt(c.D_chemicals*c.decay));// - (d/t)*exp(-t);
}

int main()
{
    Configuration::threshold = .33f;
    Configuration::D_chemicals = 10000.f;// Calculer //µm².min**-1
    Configuration::decay = 1.f;
    Configuration::D_beads = 12.f;

    std::time_t st = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Started computation at " << std::ctime(&st)<<std::endl;

    Display lcd(640,640,false);
    std::ofstream f_out("data.log");

    Configuration params();
    params.ReadConf("../parameters");

    plateau * surf = new plateau(params.getBalls());
    surf->init(5,5);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for(int i = 0 ; i < params.totalSteps ; i ++ )
    {

        std::cout<<"# Step : " << i <<std::endl<<std::endl;
        if(i%5==0)
        {
            lcd.render(surf->balls,params);
            lcd.make();
        }
       #pragma omp parallel for
       for(int j = 0 ; j < surf->balls->size() ; j ++)
        {
            surf->balls->at(j).compute(0.1);
            surf->balls->at(j).log(Ball::logLevel::concentration | Ball::logLevel::reaction, f_out); //plutôt avec une queue !
            if(Configuration::gBrownian)
                surf->balls->at(j).move();
        }



        #pragma omp simd //ivdep
        for(int i = 0 ; i < surf->balls->size() ; i ++)
           (*(*surf->balls)[i].species)*=params.decay;

        std::vector<Ball> temp(*surf->balls);

        for(int i = 0 ; i < surf->balls->size() -1 ; i ++)
        {
            for(int j = i+1 ; j <  surf->balls->size() ; j++)
            {
                float distance = d((surf->balls->at(i)),(surf->balls->at(j)));
                if (distance < params.threshold)
                {
                    (*surf->balls)[i].species->pConc[0] += mixingCoeff(distance,params) * (temp.at(j).computeSprayed().pConc[0]);
                    (*surf->balls)[i].species->pConc[1] += mixingCoeff(distance,params) * (temp.at(j).computeSprayed().pConc[1]);
                    (*surf->balls)[i].species->pConc[2] += mixingCoeff(distance,params) * (temp.at(j).computeSprayed().pConc[2]);
                }
//A changer

            }
        }

    }



    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Time elapsed : "<<elapsed_seconds.count()<<"s"<<std::endl;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)<<std::endl;

    return 0;
}

