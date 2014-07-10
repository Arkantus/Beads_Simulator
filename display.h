#ifndef DISPLAY_H
#define DISPLAY_H
#include "ball.h"
#include "configuration.h"
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include"misc.hpp"



class Display
{
public:
    Display();
    Display(int x, int y, bool SDL=false);
    void render(const std::vector<Ball> *, const Configuration &);
    void make();
    void OutputRawData(const std::vector<Ball> *);


private:
    void initSDL();
    void savePPM();
    void drawPPM(const std::vector<Ball> *, const Configuration &);
    void drawSDL(const std::vector<Ball> *, const Configuration &);

    bool SDL;
    SDL_Window *window;
    SDL_Renderer *renderer;
    uint32_t * screen;
    SDL_Surface *surface;
    SDL_Texture *tex ;
    uint8_t* scrrenCahr;

    void blit();

    int w;
    int h;
};

#endif // DISPLAY_H
