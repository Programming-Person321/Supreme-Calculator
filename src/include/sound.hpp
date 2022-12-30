#ifndef SOUND_HPP
#define SOUND_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"

bool soundInit();
Mix_Chunk* loadSound(const char* name);
Uint32 getChunkTimeMilliseconds(Mix_Chunk* chunk);
void beep(float freq, int duration);
void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes);

// class soundStruct{
// public:
//     float freq;

//     void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes);
// };

#endif