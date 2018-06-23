#include "sound_effect.h"
#include <limits.h>

int GLOBAL_CHANNEL_COUNTER = 1;

SoundEffect::SoundEffect(void) {
  this->sound = NULL;
  this->music = NULL;

  this->playingMusic = false;
  this->playingSound = false;

  if (GLOBAL_CHANNEL_COUNTER == INT_MAX) {
    GLOBAL_CHANNEL_COUNTER = 1;
  }

  this->channel = GLOBAL_CHANNEL_COUNTER++;

  Mix_AllocateChannels(Mix_AllocateChannels(-1) + 1);
}

SoundEffect::~SoundEffect() {
  this->freeSound();
  this->freeMusic();
}

void SoundEffect::freeSound(void) {
  this->playingSound = false;
  Mix_HaltChannel(this->channel);
  if (this->sound) {
    Mix_FreeChunk(this->sound);
    this->sound = NULL;
  }
}

void SoundEffect::freeMusic(void) {
  if (this->music) {
    Mix_HaltChannel(this->channel);
    Mix_FreeMusic(this->music);
    this->music = NULL;
  }
}

void SoundEffect::setSound(std::string path) {
  this->freeSound();
  this->sound = Mix_LoadWAV(path.c_str());
  if (!this->sound) {
    throw View::Exception("%s %s. SDL_Error: %s.", ERR_MSG_LOADING_SOUND, path.c_str(), Mix_GetError());
  }
}

void SoundEffect::setMusic(std::string path) {
  this->freeMusic();
  this->music = Mix_LoadMUS(path.c_str());
  if (!this->music) {
    throw View::Exception("%s %s. SDL_Error: %s.", ERR_MSG_LOADING_SOUND, path.c_str(), Mix_GetError());
  }
}

void SoundEffect::playSound(int loops) {
  if (Mix_Playing(this->channel) == 0) {
    this->playingSound = false;
  }

  if (!this->playingSound && this->sound) {
    Mix_PlayChannel(this->channel, this->sound, loops);
    this->playingSound = true;
  }
}

void SoundEffect::stopSound(void) {
  Mix_HaltChannel(this->channel);
}

void SoundEffect::playMusic(int loops) {
  if (!Mix_PlayingMusic()) {
    this->playingMusic = false;
    if (this->music) {
      Mix_PlayMusic(this->music, loops);
      this->playingMusic = true;
    }
  }

  if (Mix_PausedMusic()) {
    Mix_ResumeMusic();
  }  
}

void SoundEffect::increaseMusicVolume(int inc) {
  this->musicVolume = Mix_VolumeMusic(-1);
  this->musicVolume + inc > MIX_MAX_VOLUME ? Mix_VolumeMusic(MIX_MAX_VOLUME) : Mix_VolumeMusic(this->musicVolume + inc);
}

void SoundEffect::decreaseMusicVolume(int dec) {
  this->musicVolume = Mix_VolumeMusic(-1);
  this->musicVolume - dec < 0 ? Mix_VolumeMusic(0) : Mix_VolumeMusic(this->musicVolume - dec);
}

bool SoundEffect::isPlaying(void) {
  return Mix_Playing(this->channel) != 0;
}