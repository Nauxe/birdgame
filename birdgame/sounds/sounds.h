#pragma once

#include <SDL3/SDL.h>

struct Sound {
  Uint8 *wav_data;
  Uint32 wav_data_len;
  SDL_AudioStream *stream;
};

struct SoundPack {
  Sound birdBoop;
};

bool InitSound(SDL_AudioDeviceID audioDevice, const char *fname, Sound *sound);

bool PlaySound(Sound *sound);
