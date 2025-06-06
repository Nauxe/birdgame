#pragma once

#include <SDL3/SDL.h>

#define BOOP_FRAMES 3
#define MAX_BOOP_FRAMES 10
#define BOOP_SIZE_MULT 0.1

class BirdContext {
private:
  int boopFrames;
  float texture_width;
  float texture_height;
  SDL_Texture *curTexture;

public:
  BirdContext(float x_loc, float y_loc);

  float width;
  float height;
  float x_loc;
  float y_loc;
  inline SDL_Texture *GetCurTexture();
  SDL_AppResult SetCurTexture(SDL_Texture *texture);
  SDL_AppResult BoopBird();
  SDL_AppResult BirdIterate();
};

inline SDL_Texture *BirdContext::GetCurTexture() { return this->curTexture; }
