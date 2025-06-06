#pragma once

#include <SDL3/SDL.h>
#include <memory>

#define BOOP_FRAMES 10
#define MAX_BOOP_FRAMES 15
#define BOOP_SIZE_MULT 0.05
#define BOOP_ANIM_FRAMES 15

struct BirdTextureSet {
  SDL_Texture *birdTexIdle, *birdTexFootUp;
};

class BirdContext {
private:
  int boopFrames;
  float texture_width;
  float texture_height;
  SDL_Texture *curTexture;
  std::unique_ptr<BirdTextureSet> birdTextureSet;

  SDL_AppResult SetCurTexture(SDL_Texture *texture);

public:
  BirdContext(float x_loc, float y_loc);

  float width;
  float height;
  float x_loc;
  float y_loc;

  inline SDL_Texture *GetCurTexture();

  SDL_AppResult InitalizeBirdTextures(SDL_Texture *birdTexIdle,
                                      SDL_Texture *birdTexFootUp);
  SDL_AppResult BoopBird();
  SDL_AppResult BirdIterate();
};

inline SDL_Texture *BirdContext::GetCurTexture() { return this->curTexture; }
