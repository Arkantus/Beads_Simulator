#include <iostream>
#include"configuration.h"
#include"plateau.h"
#include"ball.h"
//#include"omp.h"

using namespace std;

int main()
{
    Configuration *params = new Configuration();
    params->ReadConf("../parameters");

    plateau * surf = new plateau(params->getBalls());
    surf->init(5,5);

    for(int i = 0 ; i < params->totalSteps ; i ++ )
    {
       // #pragma omp parralell for
        for(auto b : *(surf->balls))
        {
            b->compute(params->reactSteps); //b->compute...
            b->move(); //peu être mal placé
        }

        for(int i = 0 ; i < surf->balls->size() -1 ; i ++)
        {
            //#prama omp parrall for
            for(int j = i+1 ; j <  surf->balls->size() ; j++)
            {
                float distance = d(*(surf->balls->at(i)),*(surf->balls->at(j)));
                if (distance < params->threshold)
                {
                    Species temp = *(surf->balls->at(i)->species);
                    //omp atomic
                    //surf->balls[i] += mixingCoeff(distance) * surf->balls->at(j).species; //NAWAK
                    //surf->balls[j] += mixingCoeff(distance) * temp;
                }
            }
        }
    }
    return 0;
}

