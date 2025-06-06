#include "utils.h"

/////////////////////////////////////////////////////////////////////////////
/// Helper Functions
/////////////////////////////////////////////////////////////////////////////

SDL_AppResult SDL_Fail() {
  SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
  return SDL_APP_FAILURE;
}

void MoveAppWindowCenterToMouse(AppContext *app) {
  float x, y;
  SDL_GetGlobalMouseState(&x, &y);
  SDL_SetWindowPosition(app->window, x - app->mouseContext->win_x,
                        y - app->mouseContext->win_x);
}
