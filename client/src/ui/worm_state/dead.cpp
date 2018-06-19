#include "dead.h"

#define DEAD_RATIO_EXPLOSION 50

View::Dead::Dead(View::Worm * worm, SDL_Renderer * r) : 
  explosion(r, DEAD_RATIO_EXPLOSION, "Bazooka"){
  this->state = WS_DEAD;
  this->context = worm;
  
  this->textureDying.loadFromFile(gPath.PATH_WORM_DIE, r);
  this->spriteDying.setSpriteSheet(&this->textureDying);
  this->spriteDying.changeSpriteType(ONLY_GOING);

  const char * graves[] = {
    //gPath.PATH_GRAVE_1.c_str(),
    gPath.PATH_GRAVE_2.c_str(),
    gPath.PATH_GRAVE_3.c_str()
    //gPath.PATH_GRAVE_4.c_str(),
    //gPath.PATH_GRAVE_5.c_str(),
    //gPath.PATH_GRAVE_6.c_str()
  };

  const char * sounds[] = {
    gPath.PATH_SOUND_DIE.c_str(),
    gPath.PATH_SOUND_BYE.c_str()
  };

  this->textureGrave.loadFromFile(graves[rand() % 2], r);
  this->spriteGrave.setSpriteSheet(&this->textureGrave);
  this->spriteGrave.changeSpriteType(INFINITE_GOING_AND_BACK);

  this->sound.setSound(sounds[rand() % 2]);
  this->sound.playSound(0);

  this->dying = true;
}

View::Dead::~Dead() {

}

void View::Dead::render(SDL_Renderer * r, int camX, int camY, worm_inclination_t incl, bool mirrored, int angle) {
  if (this->dying) {
    if (!this->spriteDying.finished()) {
      SDL_Rect clip = this->spriteDying.getNextClip();
      View::Texture & current = this->textureDying;
      if (mirrored) {
        current.render(
          r, 
          this->context->getX() - current.getWidth() / 2 - camX, 
          this->context->getY() - current.getWidth() / 2 - camY, 
          &clip, 
          0, 
          NULL, 
          SDL_FLIP_HORIZONTAL
        );
      } else {
        current.render(
          r, 
          this->context->getX() - current.getWidth() / 2 - camX, 
          this->context->getY() - current.getWidth() / 2 - camY, 
          &clip
        );
      }
    } else {
      this->dying = false;
    }
  } else if (!this->explosion.finishedExplosion()) {
    this->explosion.setX(this->context->getX());
    this->explosion.setY(this->context->getY());
    this->explosion.render(r, camX, camY);
  } else {
    SDL_Rect clip = this->spriteGrave.getNextClip();
    this->textureGrave.render(
      r,
      this->context->getX() - this->textureGrave.getWidth() / 2 - camX,
      this->context->getY() - this->textureGrave.getWidth() / 2 - camY,
      &clip
    );
  }
}