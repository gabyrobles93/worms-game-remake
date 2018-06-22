#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "view_exceptions.h"

extern int GLOBAL_CHANNEL_COUNTER;

class SoundEffect {
  private:
    Mix_Chunk * sound;
    Mix_Music * music;

    bool playingSound;
    bool playingMusic;

    int channel;
    int musicVolume;

    // Libera la memoria del sonido
    void freeSound(void);

    // Libera la memoria de la musica
    void freeMusic(void);

    void channelFinished(int);

  public:
    // Constructor por defecto
    SoundEffect();

    // Destructor, libera el Mix_Chunk
    ~SoundEffect();

    // Setea los archivos de sonidos
    void setSound(std::string);
    void setMusic(std::string);

    // Reproduce el sonido loops+1 
    // veces. -1: reproduce eternamente
    // hasta que se lo detenga.
    void playSound(int loops = -1);

    // Reproduce la musica loops+1 
    // veces. -1: reproduce eternamente
    // hasta que se lo detenga.
    void playMusic(int loops = -1);

    // Aumenta el volumen de la musica
    void increaseMusicVolume(int inc = 10);
  
    // Disminuye el volumen de la musica
    void decreaseMusicVolume(int dec = 10);

    // Para el sonido
    void stopSound(void);
};

#endif