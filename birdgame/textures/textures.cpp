#include "textures.h"
#include <SDL3_image/SDL_image.h>

SDL_AppResult LoadTextureFromPath(AppContext **appPtr, SDL_Texture **texture,
                                  const char *path) {
  AppContext *app = *appPtr;

  SDL_Surface *surface = IMG_Load(path);
  if (not surface) {
    return SDL_Fail();
  }

  *texture = SDL_CreateTextureFromSurface(app->renderer, surface);
  if (not texture) {
    return SDL_Fail();
  }

  SDL_DestroySurface(surface);
  return SDL_APP_CONTINUE;
}

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(AppContext *app, SDL_Texture *texture, float x,
                               float y, float texture_width,
                               float texture_height, float rotation = 0.0f) {
  SDL_FRect dst_rect;
  dst_rect.x = x - texture_width / 2.0f;
  dst_rect.y = y - texture_height / 2.0f;
  dst_rect.w = (float)texture_width;
  dst_rect.h = (float)texture_height;

  SDL_FPoint center;
  center.x = texture_width / 2.0f;
  center.y = texture_height / 2.0f;

  SDL_RenderTextureRotated(app->renderer, texture, NULL, &dst_rect, rotation,
                           &center, SDL_FLIP_NONE);

  return SDL_APP_CONTINUE;
}

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(AppContext *app, SDL_Texture *texture, float x,
                               float y, float rotation) {
  float texture_width, texture_height;
  SDL_GetTextureSize(texture, &texture_width, &texture_height);

  return DisplayTextureAt(app, texture, x, y, texture_width, texture_height,
                          rotation);
}

SDL_AppResult LoadTextures(AppContext **appPtr) {
  AppContext *app = *appPtr;

  SDL_Texture *birdTex1, *birdTex2, *pipeTex1, *pipeTex2, *cloudTex;
  LoadTextureFromPath(appPtr, &birdTex1, (ASSETS_PATH + "bird1.png").c_str());
  LoadTextureFromPath(appPtr, &birdTex2, (ASSETS_PATH + "bird2.png").c_str());
  LoadTextureFromPath(appPtr, &cloudTex, (ASSETS_PATH + "cloud.png").c_str());

  if (not birdTex1 || not birdTex2 || not pipeTex1 || not pipeTex2 ||
      not cloudTex) {
    return SDL_Fail();
  }

  app->textureSet = std::make_unique<TextureSet>(TextureSet{
      .birdTex1 = birdTex1,
      .birdTex2 = birdTex2,
      .cloudTex = cloudTex,
  });

  return SDL_APP_CONTINUE;
}

/////////////////////////////////////////////////////////////////////////////
/// Rendering Functions
/////////////////////////////////////////////////////////////////////////////

SDL_AppResult RenderBird(AppContext *app) {
  float bird_center_x = app->bird->x_loc;
  float bird_center_y = app->bird->y_loc;
  float bird_width = app->bird->width;
  float bird_height = app->bird->height;

  if (app->bird->boopFrames > 0) {
    bird_width += bird_width * app->bird->boopFrames * BOOP_SIZE_MULT;
    bird_height += bird_height * app->bird->boopFrames * BOOP_SIZE_MULT;
  }

  DisplayTextureAt(app, app->bird->curTexture, bird_center_x, bird_center_y,
                   bird_width, bird_height);
  return SDL_APP_CONTINUE;
}
