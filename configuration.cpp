#include "configuration.h"

int Configuration::totalSteps = 100;
float Configuration::threshold = 1.f;
float Configuration::D_chemicals =1000.f;// 10000.f;// Calculer //µm².min**-1
float Configuration::k_decay = .9f;
float Configuration::D_beads = 12.f;
float Configuration::beadSize = 10.f; //µm


Configuration::Configuration(){}

void Configuration::convert()
{
    float surf = mp["sx"] * mp["sy"];
    Configuration::D_chemicals = mp["Diffusivity_Chemi"] / surf;
    Configuration::D_beads = mp["Diffusivity_Beads"] / surf;
    Configuration::k_decay = mp["Decay_k"];
    Configuration::beadSize = mp["BeadSize"] / ((mp["sx"] + mp["sy"])/2);
}

void Configuration::ReadConf(std::string file)
{
    std::string name_world;
    std::ifstream params;
    params.open(file);
    std::string temp;
    if(params.is_open())
    {
        while(std::getline(params,temp))
        {
            std::string buf;
            std:: stringstream ss(temp);
            std::vector<std::string> tokens;
            while(ss >> buf)
                tokens.push_back(buf);
            if(tokens.size() == 2 && tokens[0] != "world")
                mp[tokens[0]] = std::stof(tokens[1]);
            else if(tokens[0] == "world")
                name_world = tokens[1];
        }
        params.close();
        convert();
    }
    else
    {

    }

    std::ifstream world;
    world.open(name_world);
    if(!world.is_open())
    {
        std::cerr<<"File " <<name_world<< " was not found, using default values"<<std::endl;
        createDefaultWorld(3);
    }
    else
    {
        tbr =new std::vector<Ball>;
        //int i = 0 ;
        std::string posi;
        bool check = std::getline(world,temp);
        while(check)
        {
            //if(temp == std::string(""))
            //    continue;
            std::string buf;
            std:: stringstream ss(temp);
            std::vector<std::string> tokens;
            while(ss >> buf)
                tokens.push_back(buf);

            int nbBalls =std::stoi(tokens[1]);

            std::getline(world,temp);
            posi = temp;
            std::getline(world,temp);
            int numEq = std::stoi(temp);
            std::vector<Reaction> reac;//(numEq);
            for(int i = 0 ; i < numEq ; i++)
            {
                std::string eq,kpkm;
                std::getline(world,eq);
                std::getline(world,kpkm);
                size_t pos = 0;
                float kp,km;
                kp = std::stof(kpkm,&pos);
                km = std::stof(kpkm.substr(pos),&pos);
                //reac[i] = Reaction(eq,kp,km);
                reac.push_back(Reaction(eq,kp,km));
            }
            size_t pos = 0;
            std::string concent;
            std::getline(world,concent);
            int nprod = mp["NumProd"];  //TODO Changer ça
            float * conc = new float[nprod];
            for(int j = 0; j < nprod ; j++)
            {
                conc[j] = std::stof(concent.substr(pos),&pos);
            }
            Species* s = new Species(nprod,conc,0,conc);



            for(int i = 0; i < std::stoi(tokens[1]) ; i ++ )
            {
                float xy[2];
                if (posi == "rand")
                {
                    xy[0] = (float)rand()/RAND_MAX;
                    xy[1] = (float)rand()/RAND_MAX;
                }
                Ball b(s,reac,xy);
                tbr->push_back(b);
            }
            delete s;
            check = std::getline(world,temp);
        }
        world.close();
    }
}

void Configuration::createDefaultWorld(int nb)
{
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

    //tbr->shrink_to_fit(); //Fait rien en fait
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
