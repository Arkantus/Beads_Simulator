#include "configuration.h"

int Configuration::totalSteps = 10;
float Configuration::threshold = 1.f;
float Configuration::D_chemicals =1000.f;// 10000.f;// Calculer //µm².min**-1
float Configuration::decay = .9f;
float Configuration::D_beads = 12.f;


Configuration::Configuration()
{


}

void Configuration::ReadConf(std::string file = "/home/marc/workspace/synthetic_balls/world.conf")
{



    std::cout<<"Debut de ReadConf" << std::endl;
    std::string temp;
    std::ifstream world;
    world.open(file);
    if(!world.is_open())
    {
        std::cerr<<"File " <<file<< " was not found, using default values"<<std::endl;

        int nb = 50;
        tbr =new std::vector<Ball>(nb);

        for(int i = 1 ; i < nb+1; i++)
        {
            Species * s;
            float* t;
            float x = rand()/(float)RAND_MAX;
            float y = rand()/(float)RAND_MAX;
            float pos[2] = {x,y};
            std::vector<Reaction> reac;

            if(i%2 == 0)
            {
                t = new float[4];
                t[0] = 20.f;
                t[1] = 0.f;
                t[2] = 0.f;
                t[3] = 0.f;

                s = new Species(3,t,1,&t[0]);

                t[1]/=2;

                reac.push_back(Reaction("A = B", 100.f, 0.0f));
                reac.push_back(Reaction("A = C", 50.f, 0.0f));


            }
            else if ((i+2)%3 == 0)
            {
                t = new float[4];
                t[0] = 0.f;
                t[1] = 0.f;
                t[2] = 0.f;
                t[3] = 0.f;

                s = new Species(3,t,1,&t[0]);

                t[1]/=2;

                reac.push_back(Reaction("B = C", 100.f, 0.0f));
                reac.push_back(Reaction("B = A", 50.f, 0.0f));

            }
            else
            {
                t = new float[4];
                t[0] = 0.f;
                t[1] = 0.f;
                t[2] = 0.f;
                t[3] = 0.f;

                s = new Species(3,t,1,&t[0]);

                reac.push_back(Reaction("C = A", 50.f, 0.0f));
            }

            Ball k = Ball(s, reac ,pos);

                (*tbr)[i-1] = k;

                delete s;
                delete[] t;
            }

        tbr->shrink_to_fit(); //Fait rien en fait

        std::cout<<"Fin de ReadConf"<<std::endl;
    }
    else
    {
        while(std::getline(world,temp))
        {
            //settings(file,QSettings::IniFormat);
        }
        world.close();
    }
}



int Configuration::numBalls()
{
    return tbr->size();
}
#ifdef DEBUG
std::vector<Ball> *Configuration::getBalls()
{
    return tbr;
}
#else
std::vector<Ball> *Configuration::getBalls()
{
    return new std::vector<Ball>(5); //A remplir pour les tests
}
#endif
/*Configuration::~Configuration()
{
    //delete tbr;
}*/
