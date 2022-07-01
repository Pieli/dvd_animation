#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dvd.h"
#include "game.h"

void
render_experiment();

void
init();
void
clean();
void
render();
void
logic();
void
handleEvent(SDL_Event event);
void
update();

int
main(int argc, char* args[])
{
  Uint64 start, end;
  float elapsedMS;

  init();

  SDL_Event event;
  for (;;) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
    start = SDL_GetPerformanceCounter();

    handleEvent(event);
    update();
    logic();
    render();

    end = SDL_GetPerformanceCounter();
    // calculates to 60 fps
    elapsedMS = 0.0;
    elapsedMS =
      ((end - start) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;

    // Cap to 60 FPS
    if (elapsedMS <= 16.0)
      SDL_Delay(floor((1000.0 / 60) - elapsedMS));
    else
      SDL_Delay(1000 / 60);
  }
  clean();
  SDL_Quit();
}

void
init()
{
  gameInit();
  dvdInit();
}

void
clean()
{
  dvdClean();
  gameClean();
}

void
logic()
{
  // right boundary
  if (dvd.drect.x + dvd.drect.w > game.wind_w) {
    dvd.drect.x = game.wind_w - dvd.drect.w;
    dvd.x_direction *= -1;
    dvdSwapTexture();
    return;
  }
  // left boundary
  if (dvd.drect.x < 0) {
    dvd.drect.x = 0;
    dvd.x_direction *= -1;
    dvdSwapTexture();
    return;
  }

  // bottom boundary
  if (dvd.drect.y + dvd.drect.h > game.wind_h) {
    dvd.drect.y = game.wind_h - dvd.drect.h;
    dvd.y_direction *= -1;
    dvdSwapTexture();
    return;
  }

  // upper bounda->y
  if (dvd.drect.y < 0) {
    dvd.drect.y = 0;
    dvd.y_direction *= -1;
    dvdSwapTexture();
    return;
  }
}

void
update()
{
  dvdUpdate();
}

void
render()
{

  gameRender();
  dvdRender();

  // for multiple rendering
  SDL_RenderPresent(game.renderer);
}

void
handleEvent(SDL_Event event)
{
  gameInputAction(event);
}
