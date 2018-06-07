#include "sound_effect.h"
#include <limits.h>

int GLOBAL_CHANNEL_COUNTER = 0;

SoundEffect::SoundEffect(void) {
  this->sound = NULL;
  this->music = NULL;

  this->playingMusic = false;
  this->playingSound = false;

  if (GLOBAL_CHANNEL_COUNTER == INT_MAX) {
    GLOBAL_CHANNEL_COUNTER = 0;
  }

  this->channel = GLOBAL_CHANNEL_COUNTER++;
}

SoundEffect::~SoundEffect() {
  this->freeSound();
  this->freeMusic();
}

void SoundEffect::freeSound(void) {
  this->playingSound = false;
  if (this->sound) {
    Mix_FreeChunk(this->sound);
    this->sound = NULL;
  }
}

void SoundEffect::freeMusic(void) {
  if (this->music) {
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
