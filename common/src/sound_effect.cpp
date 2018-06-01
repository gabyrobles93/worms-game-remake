#include "sound_effect.h"

SoundEffect::SoundEffect(void) {
  this->sound = NULL;
  this->music = NULL;

  this->playingMusic = false;
  this->playingSound = false;
}

SoundEffect::~SoundEffect() {
  this->freeSound();
  this->freeMusic();
}

void SoundEffect::freeSound(void) {
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
  if (!this->playingSound && this->sound) {
    Mix_PlayChannel(-1, this->sound, loops);
  }
}

void SoundEffect::stopSound(void) {
  this->freeSound();
}