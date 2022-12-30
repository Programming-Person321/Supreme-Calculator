#include "include/sound.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Initializes the application data
bool soundInit() 
{
    // memset(_sample, 0, sizeof(Mix_Chunk*) * 2);

    // Set up the audio stream
    if(SDL_Init(SDL_INIT_AUDIO) != 0) puts("SDL Failed to init audio");
    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    result = Mix_AllocateChannels(4);
    if( result < 0 )
    {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());
        exit(-1);
    }

    return true;
}

Mix_Chunk* loadSound(const char* name){
    // Load waveforms
        Mix_Chunk* sound = Mix_LoadWAV(name);
        if( sound == NULL )
        {
            fprintf(stderr, "Unable to load wave file: %s\n", name);
        }

        return sound;
}

Uint32 getChunkTimeMilliseconds(Mix_Chunk* chunk)
{
Uint32 points = 0;
Uint32 frames = 0;
int freq = 0;
Uint16 fmt = 0;
int chans = 0;
// Chunks are converted to audio device format… /
if (!Mix_QuerySpec(&freq, &fmt, &chans))
return 0; // never called Mix_OpenAudio()?!

 /* bytes / samplesize == sample points */
 points = (chunk->alen / ((fmt & 0xFF) / 8));

 /* sample points / channels == sample frames */
 frames = (points / chans);

 /* (sample frames * 1000) / frequency == play length in ms */
 return ((frames * 1000) / freq);
}

float freq = 0.0f;
void beep(float _freq, int duration){
    int sampleNum = 0;
    freq = _freq;

    SDL_AudioSpec want;
    want.freq = 44100; // number of samples per second
    want.format = AUDIO_S16SYS; // sample type (here: signed short i.e. 16 bit)
    want.channels = 1; // only one channel
    want.samples = 2048; // buffer-size
    want.callback = audio_callback; // function SDL calls periodically to refill the buffer
    want.userdata = &sampleNum; // counter, keeping track of current sample number
    
    SDL_AudioSpec have;
    if(SDL_OpenAudio(&want, &have) != 0) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
    if(want.format != have.format) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");

    SDL_PauseAudio(0); // start playing sound
    SDL_Delay(duration); // wait while sound is playing
    SDL_PauseAudio(1); // stop playing sound

    SDL_CloseAudio();
}

void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
{
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS
    int &sample_nr(*(int*)user_data);

    for(int i = 0; i < length; i++, sample_nr++)
    {
        double time = (double)sample_nr / (double)44100;
        buffer[i] = (Sint16)(28000 * sin(2.0f * M_PI * freq * time)); // render 441 HZ sine wave
    }
}
