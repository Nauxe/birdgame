#pragma once

#include "../utils/utils.h"
#include <string>

static std::string ASSETS_PATH = "./assets/";

SDL_AppResult LoadTextureFromPath(AppContext **appPtr, SDL_Texture **texture,
                                  const char *path);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(AppContext *app, SDL_Texture *texture, float x,
                               float y, float rotation = 0.0f);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(AppContext *app, SDL_Texture *texture, float x,
                               float y, float rotation);

SDL_AppResult LoadTextures(AppContext **appPtr);

SDL_AppResult RenderBird(AppContext *app);
