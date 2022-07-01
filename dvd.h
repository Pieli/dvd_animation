#ifndef DVD_H
#define DVD_H

#include <SDL2/SDL.h>


typedef struct Dvd
{
  SDL_Texture* texture;
  SDL_Texture* all_textures[4];
  SDL_Rect srect;
  SDL_Rect drect;
  int y_direction;
  int x_direction;
} Dvd;


extern Dvd dvd;

void dvdInit();
void dvdUpdate();
void dvdRender();
void dvdClean();
void dvdSwapTexture();

#endif
