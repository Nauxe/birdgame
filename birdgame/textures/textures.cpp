#include "textures.h"
#include <SDL3_image/SDL_image.h>
#include <string>

static std::string ASSETS_PATH =
    "./assets/"; // Loading images uses the path from the location in which the
                 // executable is run from.
                 // Note: Loading sounds uses the path from which the executable
                 // is located.

/////////////////////////////////////////////////////////////////////////////
/// Rendering Helper Functions
/////////////////////////////////////////////////////////////////////////////

bool LoadTextureFromPath(SDL_Renderer *renderer, SDL_Texture **texture,
                         const char *path) {
  SDL_Surface *surface = IMG_Load(path);
  if (not surface) {
    return false;
  }

  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (not texture) {
    return false;
  }

  SDL_DestroySurface(surface);
  return true;
}

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
bool DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture, float x,
                      float y, float texture_width, float texture_height,
                      float rotation) {
  SDL_FRect dst_rect;
  dst_rect.x = x - texture_width / 2.0f;
  dst_rect.y = y - texture_height / 2.0f;
  dst_rect.w = (float)texture_width;
  dst_rect.h = (float)texture_height;

  SDL_FPoint center;
  center.x = texture_width / 2.0f;
  center.y = texture_height / 2.0f;

  return SDL_RenderTextureRotated(renderer, texture, NULL, &dst_rect, rotation,
                                  &center, SDL_FLIP_NONE);
}

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
bool DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture, float x,
                      float y, float rotation) {
  float texture_width, texture_height;
  if (!SDL_GetTextureSize(texture, &texture_width, &texture_height)) {
    return false;
  }

  return DisplayTextureAt(renderer, texture, x, y, texture_width,
                          texture_height, rotation);
}

bool LoadTextureSet(SDL_Renderer *renderer,
                    std::unique_ptr<TextureSet> &textureSet) {
  SDL_Texture *birdTex1, *birdTex2, *cloudTex;
  LoadTextureFromPath(renderer, &birdTex1, (ASSETS_PATH + "bird1.png").c_str());
  LoadTextureFromPath(renderer, &birdTex2, (ASSETS_PATH + "bird2.png").c_str());
  LoadTextureFromPath(renderer, &cloudTex, (ASSETS_PATH + "cloud.png").c_str());

  if (not birdTex1 || not birdTex2 || not cloudTex) {
    return false;
  }

  textureSet->birdTex1 = birdTex1;
  textureSet->birdTex2 = birdTex2;
  textureSet->cloudTex = cloudTex;

  return true;
}

/////////////////////////////////////////////////////////////////////////////
/// Rendering Functions
/////////////////////////////////////////////////////////////////////////////

bool RenderBird(AppContext *app) {
  float bird_center_x = app->bird->x_loc;
  float bird_center_y = app->bird->y_loc;
  float bird_width = app->bird->width;
  float bird_height = app->bird->height;

  return DisplayTextureAt(app->renderer, app->bird->GetCurTexture(),
                          bird_center_x, bird_center_y, bird_width,
                          bird_height);
}
