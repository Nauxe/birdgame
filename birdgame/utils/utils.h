#pragma once

#include "../bird/bird.h"
#include "../sounds/sounds.h"
#include <SDL3/SDL.h>
#include <memory>

/////////////////////////////////////////////////////////////////////////////
/// Structs
/////////////////////////////////////////////////////////////////////////////

struct TextureSet {
  SDL_Texture *birdTex1, *birdTex2, *cloudTex;
};

struct MouseContext {
  bool isHeld;
  float win_x;
  float win_y;
};

struct AppContext {
  int frameNumber;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::unique_ptr<TextureSet> textureSet;
  std::unique_ptr<SoundPack> soundPack;
  SDL_AudioDeviceID audioDevice;
  SDL_AppResult app_quit = SDL_APP_CONTINUE;
  std::unique_ptr<BirdContext> bird;
  Uint64 fps;
  Uint64 prevTickCount;
  std::unique_ptr<MouseContext> mouseContext;
};

/////////////////////////////////////////////////////////////////////////////
/// Helper Functions
/////////////////////////////////////////////////////////////////////////////
SDL_AppResult SDL_Fail();

void MoveAppWindowCenterToMouse(AppContext *app);
