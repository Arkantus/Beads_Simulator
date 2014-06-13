#include "plateau.h"

plateau::plateau(std::vector<Ball*> *p) :
 balls(p)
{
}

void plateau::init(int dx, int dy)
{
   //surface = std::vector<std::vector<Species*>> (dx);
  /* for(int i = 0 ; i < dx ; i++)
   {
       surface[i].resize(dy);
#ifdef DEBUG
       for(int j = 0 ; j  < dy ; j++)
       {
           float t[2] = {(float)j,(float)j};
           surface[i][j] = new Species(2,t, 2,t);
       }
#endif
   }*/
}
