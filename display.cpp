#include "display.h"

Display::Display(int _w, int _h, bool _SDL) : w(_w), h(_h), SDL(_SDL)
{
    if(SDL == false)
    {
        scrrenCahr = new uint8_t[w*h*3];
        if(!scrrenCahr)
        {
            std::cerr << "Echec d'initialisation du tableau Erreur IDD3" << std::endl;
            exit(2);
        }
    }
    else
        initSDL();
}

void Display::initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr<<"SDL_Init Error: "<<SDL_GetError() <<std::endl;
        //return 1;
    }
    window = SDL_CreateWindow("Synthetic Balls Simulator", 100,100, w, h,SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        std::cerr<<"SDL_CreateWindow Error: "<<SDL_GetError()<<std::endl;
        SDL_Quit();
        //return 1;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        std::cerr<<"SDL_CreateRenderer Error: "<<SDL_GetError()<<std::endl;
        SDL_Quit();
        //return 1;
    }

    Uint32 rmask, gmask, bmask, amask;

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;

    surface = SDL_CreateRGBSurface(0, w, h, 32,
                                   rmask, gmask, bmask, amask);
    if(surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

     tex = SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Display::render(const std::vector<Ball>* vb, const Configuration& config)
{
    if(SDL == false)
        drawPPM(vb,config);
    else
        drawSDL(vb,config);
}

void Display::make()
{
    if(SDL == false)
        savePPM();
    else
        blit();
}

void Display::DrawMultiPPM(const std::vector<Ball>* vb, const Configuration& config, std::string output)
{
    static int cmp = 0;

    FILE* out = fopen((output+std::to_string(cmp)).c_str(),"wb");
    int sideSize = 640/4;
    uint8_t* table,r[(sideSize)*(sideSize)],g[(sideSize)*(sideSize)],bb[(sideSize)*(sideSize)],s[(sideSize)*(sideSize)];

    for(int k = 0 ; k < vb->size() ; k ++)
    {
    Ball b = vb->at(k);

    for(int i = 0 ; i < this->w ; i++)
            {
                for(int j = 0 ; j < this->h ; j++)
                {
                    float coeff = 8.5f;

                    int x = (int) ( b.coord[0] * w);
                    int y = (int) ( b.coord[1] * h);

                    if((x+i) <0 || (x+i)>w || (y+j)>h || (y+j)<0)
                        continue;

                    int position = (x+i) + (y+j)*w;
                    float rCoord = (std::hypot(i,j)/(float)w);
                    float attenuation = mcDonald(rCoord);
                    //#pragma omp atomic
                    scrrenCahr[position*3 + 0] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(0));
                    scrrenCahr[position*3 + 1] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(1));
                    scrrenCahr[position*3 + 2] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(2));
                    r [position/4] += (uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(0));
                    g [position/4] += (uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(1));
                    bb[position/4] += (uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(2));
                }

            }

        //float *table;

        for(int i = 0 ; i < h ; i ++)
        {
            for(int j = 0 ; j < w ; j ++)
            {
                fprintf(out,"%" PRIu8,scrrenCahr[i + j*w]);
            }
            switch(i/sideSize)
            {
                case(0):
                    table = r;
                    break;
                case(1):
                    table = g;
                    break;
                case(2):
                    table = bb;
                    break;
            }
            int i_temp = i%sideSize;
            for(int j = 0 ; j < sideSize ; j ++)
            {
                fprintf(out,"%" PRIu8,table[i_temp + j*w]);
            }

        }
    }
}

void Display::drawPPM(const std::vector<Ball>* vb, const Configuration& config)
{
#pragma simd
    for(int ite = 0 ; ite < w*h*3 ; ite++)
        scrrenCahr[ite] = (uint8_t)0;

    for(int k = 0 ; k < vb->size() ; k ++)
    {
        Ball b = vb->at(k);

        int x = (int) ( b.coord[0] * w);
        int y = (int) ( b.coord[1] * h);

        int mix_x = Configuration::threshold * w;
        int mix_y = Configuration::threshold * h;

        //#pragma omp parallel for collapse(2)
        #pragma omp simd for collapse(2)
        for(int j = - mix_y+1 ; j < mix_y ; j++) //echange des loops
        {
            for(int i = -mix_x+1 ; i < mix_x ; i++)
            {
                float coeff = 10.f;

                if((x+i) <0 || (x+i)>w || (y+j)>h || (y+j)<0)
                    continue;

                int position = (x+i) + (y+j)*w;
                float rCoord = (std::hypot(i,j)/(float)w);
                float attenuation = mcDonald(rCoord);
                //#pragma omp atomic
                scrrenCahr[position*3 + 0] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(0));
                scrrenCahr[position*3 + 1] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(1));
                scrrenCahr[position*3 + 2] +=(uint8_t) (coeff * attenuation * b.productedSpecies.getProductionConcentration(2));
            }
        }
        scrrenCahr[(x+y*w)*3 + 0] = (uint8_t)0xff;
        scrrenCahr[(x+y*w)*3 + 1] = (uint8_t)0xff;
        scrrenCahr[(x+y*w)*3 + 2] = (uint8_t)0xff;
    }
}

void Display::drawSDL(const std::vector<Ball> * vb, const Configuration & config)
{
    for(int ite = 0 ; ite < w*h ; ite++)
        ((Uint32 *)surface->pixels)[ite] = 0;

    //Omp parrallel ? et Atomic après?
    for(int k = 0 ; k < vb->size() ; k ++)
    {
        Ball b = vb->at(k);

        int x = (int) ( b.coord[0] * w);
        int y = (int) ( b.coord[1] * h);

        int mix_x = Configuration::threshold * w;
        int mix_y = Configuration::threshold * h;


        for(int i = -mix_x+1 ; i < mix_x ; i++)
        {
            for(int j = - mix_y+1 ; j < mix_y ; j++)
            {
                if((x+i) <0 || (x+i)>w || (y+j)>h || (y+j)<0)
                    continue;
                int position = (x+i) + (y+j)*w;
                uint8_t r,g,bb,a;
                r = ((Uint32 *)surface->pixels)[position] & 0x000000ff;
                g = ((Uint32 *)surface->pixels)[position] & 0x0000ff00 >> 8 ;
                bb = ((Uint32 *)surface->pixels)[position] & 0x00ff0000 >> 16;
                a = 0x88;
                r+= (uint8_t) ( (exp(- (std::hypot(i,j)) -exp(Configuration::threshold)) )*5000.f*b.species->getProductionConcentration(0));
                g+= (uint8_t) ( (exp(- (std::hypot(i,j)) -exp(Configuration::threshold)) )*5000.f*b.species->getProductionConcentration(1));
                bb+=(uint8_t) ( (exp(- (std::hypot(i,j)) -exp(Configuration::threshold)) )*5000.f*b.species->getProductionConcentration(2));

                ((Uint32 *)surface->pixels)[position] =  r | g << 8 | bb << 16 | (uint8_t)120 << 24;
            }
        }
    }


}

void Display::OutputRawData(const std::vector<Ball> *vb)
{
    static int i = 0;
    std::string file("data_"+std::to_string(i));
    std::ofstream f_out(file);
    for(Ball b : *vb)
    {
        f_out<<b.coord[0]<<","<<b.coord[1]<<std::endl;
        f_out<<b.species->getProductionConcentration(0)<<","<<b.species->getProductionConcentration(1)<<","<<b.species->getProductionConcentration(2)<<std::endl;
    }
    f_out.close();
    i++;
}


void Display::savePPM()
{
    static int i = 0 ;
    std::string file("matrix_"+std::to_string(i)+".data");
    std::ofstream f_out(file,std::ios::binary);
    f_out<<"P6\n#comment\n"<<w<<"\n"<<h<<"\n"<<"255"<<std::endl;
    f_out.write((char*)scrrenCahr,w*h*3*sizeof(uint8_t));
    f_out.close();
    i++;
}

void Display::blit()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
}
