#include "sounds.h"

bool InitSound(SDL_AudioDeviceID audioDevice, const char *fname, Sound *sound) {
  bool retval = false;
  SDL_AudioSpec spec;
  char *wav_path = NULL;

  /* Load the .wav files from wherever the app is being run from. */
  SDL_asprintf(&wav_path, "%s%s", SDL_GetBasePath(),
               fname); /* allocate a string of the full file path */
  if (!SDL_LoadWAV(wav_path, &spec, &sound->wav_data, &sound->wav_data_len)) {
    SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
    return false;
  }

  // Create an audio stream. Set the source format to the wav's format (what
  // we'll input), leave the dest format NULL here (it'll change to what the
  // device wants once we bind it).
  sound->stream = SDL_CreateAudioStream(&spec, NULL);
  if (!sound->stream) {
    SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
  } else if (!SDL_BindAudioStream(
                 audioDevice,
                 sound->stream)) { // once bound, it'll start playing when there
                                   // is data available!
    SDL_Log("Failed to bind '%s' stream to device: %s", fname, SDL_GetError());
  } else {
    retval = true; // success!
  }

  SDL_free(wav_path); // done with this string.
  return retval;
}

bool PlaySound(Sound *sound) {
  return SDL_ClearAudioStream(sound->stream) &&
         SDL_PutAudioStreamData(sound->stream, sound->wav_data,
                                (int)sound->wav_data_len);
}
