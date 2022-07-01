#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dvd.h"
#include "game.h"

Dvd dvd;
const int SPEED = 3;

void
dvdInit()
{
  // assets
  SDL_Surface* tmpSurface;
  char* assets[4] = { "./assets/dvd_logo_blue.png",
                      "./assets/dvd_logo_green.png",
                      "./assets/dvd_logo_red.png",
                      "./assets/dvd_logo_white.png" };

  // load asset
  for (int i = 0; i < 4; i++) {
    tmpSurface = IMG_Load(assets[i]);
    dvd.all_textures[i] =
      SDL_CreateTextureFromSurface(game.renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    SDL_QueryTexture(
      dvd.all_textures[i], NULL, NULL, &dvd.drect.w, &dvd.drect.h);
  }

  // inital texture
  dvd.texture = dvd.all_textures[0];

  dvd.x_direction = 1;
  dvd.y_direction = 1;
  dvd.srect.x = 100;
  dvd.srect.y = 100;

  //  scaling
  dvd.drect.w /= 3;
  dvd.drect.h /= 3;

  // positioning
  dvd.drect.x = (1000 - dvd.drect.w) / 2;
  dvd.drect.y = (1000 - dvd.drect.h) / 2;
}

void
dvdUpdate()
{
  dvd.drect.x += SPEED * dvd.x_direction;
  dvd.drect.y += SPEED * dvd.y_direction;
}

void
dvdRender()
{
  if (SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255) != 0) {
    SDL_Log("Something failed: %s", SDL_GetError());
  }

  if (SDL_RenderCopy(game.renderer, dvd.texture, NULL, &dvd.drect) != 0) {
    SDL_Log("error during RenderCopy: %s\n", SDL_GetError());
    exit(1);
  }
}

void
dvdSwapTexture()
{
  int random = rand() % 4;
  dvd.texture = dvd.all_textures[random];
}

void
dvdClean()
{
  for (int i = 0; i < 4; i++) {
    SDL_DestroyTexture(dvd.all_textures[i]);
  }
}
