#include <iostream>
#include <chrono>
#include <ctime>
#include"configuration.h"
#include"plateau.h"
#include"ball.h"
#include"display.h"
#include"misc.hpp"
#include"omp.h"

using namespace std;


int main()
{


    std::time_t st = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Started computation at " << std::ctime(&st)<<std::endl;

    Display lcd(640,640,false);
    std::ofstream f_out("data.log");

    Configuration params;
    params.ReadConf("../parameters");

    plateau * surf = new plateau(params.getBalls());
    surf->init(5,5);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for(int i = 0 ; i < params.totalSteps ; i ++ )
    {

        std::cout<<"# Step : " << i <<std::endl<<std::endl;
        if(i%1==0)
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

        std::vector<Ball> temp(*surf->balls);

        for(int i = 0 ; i < surf->balls->size() ; i ++)
        {
            (*surf->balls)[i].species->reset();
            for(int j = 0 ; j <  surf->balls->size() ; j++)
            {
                float distance = d((surf->balls->at(i)),(surf->balls->at(j)));
                //if (distance < params.threshold)
                //{
                    (*surf->balls)[i].species->pConc[0] += mcDonald(distance) * (temp.at(j).productedSpecies.pConc[0]);
                    (*surf->balls)[i].species->pConc[1] += mcDonald(distance) * (temp.at(j).productedSpecies.pConc[1]);
                    (*surf->balls)[i].species->pConc[2] += mcDonald(distance) * (temp.at(j).productedSpecies.pConc[2]);
                //}
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

