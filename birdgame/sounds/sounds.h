#pragma once

#include <SDL3/SDL.h>
#include <memory>

struct Sound {
  Uint8 *wav_data;
  Uint32 wav_data_len;
  SDL_AudioStream *stream;
};

struct SoundPack {
  Sound birdBoop;
};

bool LoadSoundFromPath(SDL_AudioDeviceID audioDevice, Sound *sound,
                       const char *fname);

bool PlaySound(Sound *sound);

bool LoadSoundPack(SDL_AudioDeviceID audioDevice,
                   std::unique_ptr<SoundPack> &soundPack);
