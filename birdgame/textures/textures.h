#pragma once

#include "../utils/utils.h"
#include "SDL3/SDL_render.h"
#include <memory>

bool LoadTextureFromPath(SDL_Renderer *renderer, SDL_Texture **texture,
                         const char *path);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
bool DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture, float x,
                      float y, float texture_width, float texture_height,
                      float rotation = 0.0f);

// x and y are pixel locations the center of the texture should be at
// (with origin at upper left)
bool DisplayTextureAt(SDL_Renderer *renderer, SDL_Texture *texture, float x,
                      float y, float rotation = 0.0f);

bool LoadTextureSet(SDL_Renderer *renderer,
                    std::unique_ptr<TextureSet> &textureSet);

bool RenderBird(AppContext *app);
