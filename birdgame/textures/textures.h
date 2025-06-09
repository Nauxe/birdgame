#pragma once

#include "../utils/utils.h"
#include "SDL3/SDL_render.h"
#include <memory>
#include <string>

static std::string ASSETS_PATH =
    "./assets/"; // Loading images uses the path from the location in which the
                 // executable is run from.
                 // Note: Loading sounds uses the path from which the executable
                 // is located.

SDL_AppResult LoadTextureFromPath(SDL_Renderer *renderer, SDL_Texture **texture,
                                  const char *path);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture,
                               float x, float y, float texture_width,
                               float texture_height, float rotation = 0.0f);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
SDL_AppResult DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture,
                               float x, float y, float rotation = 0.0f);

SDL_AppResult LoadTextures(SDL_Renderer *renderer,
                           std::unique_ptr<TextureSet> &textureSet);

SDL_AppResult RenderBird(AppContext *app);
