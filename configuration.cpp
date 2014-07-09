#include "configuration.h"




Configuration::Configuration()
{}

void Configuration::ReadConf(std::string file = "/home/marc/workspace/synthetic_balls/world.conf")
{
    std::cout<<"Debut de ReadConf" << std::endl;
    std::string temp;
    std::ifstream world;
    world.open(file);
    if(!world.is_open())
    {
        std::cerr<<"File " <<file<< " was not found, using default values"<<std::endl;

        int nb = 9;
        totalSteps = 5000;
        tbr =new std::vector<Ball>(nb);

        for(int i = 0 ; i < nb; i++)
        {
            Species * s;
            float* t;
            float pos[2] = {(i+1)/10.f,(i+1)/10.f};
            std::vector<Reaction> reac;

            if(i%3 == 0)
            {
                t = new float[4];
                t[0] = 20.f;
                t[1] = 0.f;
                t[2] = 0.f;
                t[3] = 0.f;

                s = new Species(3,t,1,&t[0]);

                t[1]/=2;

                reac.push_back(Reaction("A = B ", .5f, 0.0f));
                //reac.push_back(Reaction("A = A A", .2f,0.f));

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

                reac.push_back(Reaction("B = A", .5f, 0.0f));
            }
            else
            {
                t = new float[4];
                t[0] = 0.f;
                t[1] = 0.f;
                t[2] = 0.f;
                t[3] = 0.f;

                s = new Species(3,t,1,&t[0]);

                t[1]/=2;

                reac.push_back(Reaction("C = C", 1.f, 0.0f));
            }

            Species * tbS = new Species(3,&t[1],0,t);

            Ball k = Ball(s, reac ,pos,tbS);

            (*tbr)[i] = k;

            delete s;
            delete tbS;
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
