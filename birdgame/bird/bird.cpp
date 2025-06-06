#include "bird.h"
#include "SDL3/SDL_init.h"

BirdContext::BirdContext(float x_loc, float y_loc) {
  this->x_loc = x_loc;
  this->y_loc = y_loc;
  this->boopFrames = 0;
  this->width = this->height = this->texture_width = this->texture_height =
      -1;                     // To be set when textures are set
  this->curTexture = nullptr; // To be set when textures are set
}

SDL_AppResult BirdContext::BoopBird() {
  this->boopFrames += BOOP_FRAMES;
  if (this->boopFrames > MAX_BOOP_FRAMES) {
    this->boopFrames = MAX_BOOP_FRAMES;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult BirdContext::BirdIterate() {
  if (this->boopFrames > 0) {
    this->width += this->width * this->boopFrames * BOOP_SIZE_MULT;
    this->height += this->height * this->boopFrames * BOOP_SIZE_MULT;

    this->boopFrames -= 1;
  } else {
    this->width = this->texture_width;
    this->height = this->texture_height;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult BirdContext::SetCurTexture(SDL_Texture *texture) {
  // Set bird texture
  this->curTexture = texture;

  // Set bird width and height
  SDL_GetTextureSize(this->curTexture, &this->texture_width,
                     &this->texture_height);
  this->width = this->texture_width;
  this->height = this->texture_height;

  return SDL_APP_CONTINUE;
}
