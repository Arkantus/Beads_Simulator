#include "configuration.h"

Configuration::Configuration():
totalSteps(5), reactSteps(1),tbr(new std::vector<Ball*>(12)), threshold(0.2), density_x(5), density_y(5), diffusionNode(3)
{}

void Configuration::setParallel(int nb, int nbMax)
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
        //default
        density_x = 5;
        density_y = 5;

        threshold = 0.2;

        //tbr = new std::vector<Ball*>(12);
        std::cout<<"ICi"<<std::endl;

        for(int i = 0 ; i < 10; i++)
        {
            float t[]= {0,0};
            //std::cout<<i<<std::endl;
            t[0] = t[1] = 0.1*(2+(float)i);
            Species *s = new Species(2,t,2,t);
            Reaction *r = new Reaction();
            Ball* k = new Ball(s, r ,2 ,t );
            //std::cout<<"juste une truc"<<std::endl;

            tbr->push_back(k);
        }
        std::cout<<"ICi"<<std::endl;
        std::flush(std::cout);

        diffusionNode = 3;
        diffusionCoeff = new float*[diffusionNode];
        for(int i = 0 ; i < diffusionNode ; i++)
            diffusionCoeff[i] = new float[diffusionNode];

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
#ifdef DEBUG
std::vector<Ball*> *Configuration::getBalls()
{
    return tbr; //A remplir pour les tests
}
#else
std::vector<Ball> *Configuration::getBalls()
{
    return new std::vector<Ball>(5); //A remplir pour les tests
}
#endif
