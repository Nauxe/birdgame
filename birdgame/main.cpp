#include "textures.h"
#include "utils.h"
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#define FPS_LIMIT 60.0f

#define WINDOW_START_WIDTH 120.0f
#define WINDOW_START_HEIGHT 120.0f

#define BOOP_FRAMES 2
#define MAX_BOOP_FRAMES 10

/////////////////////////////////////////////////////////////////////////////
/// Helper Functions
/////////////////////////////////////////////////////////////////////////////

void MoveWindowCenterToMouse(AppContext *app) {
  float x, y;
  SDL_GetGlobalMouseState(&x, &y);
  SDL_SetWindowPosition(app->window, x - app->mouseContext->win_x,
                        y - app->mouseContext->win_x);
}

/////////////////////////////////////////////////////////////////////////////
/// Initialization & Shutdown
/////////////////////////////////////////////////////////////////////////////

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  // init the library, here we make a window so we only need the Video
  // capabilities.
  if (not SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    return SDL_Fail();
  }

  // init TTF
  if (not TTF_Init()) {
    return SDL_Fail();
  }

  // create a window
  SDL_Window *window =
      SDL_CreateWindow("birdgame", WINDOW_START_WIDTH, WINDOW_START_HEIGHT,
                       SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_BORDERLESS |
                           SDL_WINDOW_TRANSPARENT | SDL_WINDOW_ALWAYS_ON_TOP);
  if (not window) {
    return SDL_Fail();
  }

  // create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (not renderer) {
    return SDL_Fail();
  }

  // init SDL Mixer
  auto audioDevice =
      SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (not audioDevice) {
    return SDL_Fail();
  }

  // print some information about the window
  SDL_ShowWindow(window);
  int width, height, bbwidth, bbheight;
  SDL_GetWindowSize(window, &width, &height);
  SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
  SDL_Log("Window size: %ix%i", width, height);
  SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
  if (width != bbwidth) {
    SDL_Log("This is a highdpi environment.");
  }
  // set up the application data
  *appstate = new AppContext{
      .frameNumber = 0,
      .window = window,
      .renderer = renderer,
      .textureSet = nullptr,
      .audioDevice = audioDevice,
      .bird = std::make_unique<BirdContext>(BirdContext{
          .width = -1,  // To be set later in init
          .height = -1, // To be set later in init
          .x_loc = (float)bbwidth / 2.0f,
          .y_loc = (float)bbheight / 2.0f,
          .boopFrames = 0,
          .curTexture = nullptr, // To be set later in init

      }),
      .fps = 0, // Set every 10 frames
      .prevTickCount = SDL_GetTicks(),
      .mouseContext = std::make_unique<MouseContext>(MouseContext{
          .isHeld = false,
          .win_x = 0.0f, // to be set only when held
          .win_y = 0.0f, // to be set only when held
      }),
  };
  auto *app = (AppContext *)*appstate;

  SDL_AppResult loadTexResult = LoadTextures(&app);
  if (loadTexResult != SDL_APP_CONTINUE) {
    return SDL_Fail();
  }

  // Set default bird texture
  app->bird->curTexture = app->textureSet->birdTex2;

  // Set bird width and height
  SDL_GetTextureSize(app->bird->curTexture, &app->bird->width,
                     &app->bird->height);

  SDL_SetRenderVSync(renderer, -1);                          // enable vysnc
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // enable blending

  srand(time(0)); // Seed rand() for pipe generation

  SDL_Log("Application started successfully!");

  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}

/////////////////////////////////////////////////////////////////////////////
/// Event handler
///
/// This function runs when a new event (mouse input, keypresses, etc) occurs
/////////////////////////////////////////////////////////////////////////////

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }

  auto *app = (AppContext *)appstate;
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      app->mouseContext->isHeld = true;
      SDL_GetGlobalMouseState(&app->mouseContext->win_x,
                              &app->mouseContext->win_y);

      int global_win_x, global_win_y;
      SDL_GetWindowPosition(app->window, &global_win_x, &global_win_y);

      app->mouseContext->win_x -= (float)global_win_x;
      app->mouseContext->win_y -= (float)global_win_y;

      app->bird->boopFrames += BOOP_FRAMES;
      if (app->bird->boopFrames < MAX_BOOP_FRAMES) {
        app->bird->boopFrames = MAX_BOOP_FRAMES;
      }
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if (event->button.button == SDL_BUTTON_LEFT) {
      app->mouseContext->isHeld = false;
    }
  }

  return SDL_APP_CONTINUE;
}

/////////////////////////////////////////////////////////////////////////
/// Per-Frame Callback
/////////////////////////////////////////////////////////////////////////////

SDL_AppResult SDL_AppIterate(void *appstate) {
  auto *app = (AppContext *)appstate;

  Uint64 frameStart = SDL_GetPerformanceCounter();

  int app_width, app_height;
  SDL_GetWindowSizeInPixels(app->window, &app_width, &app_height);

  SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 0);
  SDL_RenderClear(app->renderer); // Clear renderer before displaying textures

  RenderBird(app);

  SDL_RenderPresent(app->renderer);
  if (app->frameNumber == INT_MAX) {
    app->frameNumber = 0;
  } else {
    app->frameNumber++;
  }

  // Move window if mouse is down
  if (app->mouseContext->isHeld) {
    MoveWindowCenterToMouse(app);
  }

  // Tick boop frames
  if (app->bird->boopFrames > 0) {
    app->bird->boopFrames--;
  }

  // Log framerate
  if (app->frameNumber % 10 == 0) {
    Uint64 curTicks = SDL_GetTicks();
    app->fps = 10000 / (curTicks - app->prevTickCount);
    app->prevTickCount = curTicks;
  }

  Uint64 frameEnd = SDL_GetPerformanceCounter();
  float elapsedMS =
      (frameEnd - frameStart) / (float)SDL_GetPerformanceFrequency();

  // Cap framerate
  if (elapsedMS <= 1000.0f / FPS_LIMIT - 0.001f) {
    SDL_Delay(floor(1000.0f / FPS_LIMIT - 0.001f - elapsedMS));
  }

  return SDL_APP_CONTINUE;
}
