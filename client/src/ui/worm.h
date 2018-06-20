#ifndef __VIEW_WORM_H__
#define __VIEW_WORM_H__

#include <SDL2/SDL.h>
#include <map>
#include <string>

// States
#include "worm_state.h"
#include "breathing.h"
#include "walking.h"
#include "falling.h"
#include "flying.h"
#include "dead.h"

#include "texture.h"
#include "drawable.h"
#include "paths.h"
#include "types.h"
#include "rectangle_text.h"
#include "sprite_animation.h"
#include "sound_effect.h"
#include "font.h"
#include "sight.h"
#include "yaml.h"

namespace View {
  class WormState;

  class Worm: public Drawable {
    private:
      // Animation
      std::map<view_worm_state_t, WormState *> states;
      
      View::WormState * state;
      view_worm_state_t stateName;
      
      // Animation state
      bool grounded;
      bool mirrored;
      bool walking;
      bool falling;
      bool alive;
      bool protagonic;
      bool affectedByExplosion;
      int angleDirection;
      worm_inclination_t inclination;

      
      
      Sight sight;


      // Worm data
      size_t team;
      int health;

      // Worm data UI
      worm_data_cfg_t dataConfiguration;
      Font font;
      Texture nameText;
      Texture healthText;
      RectangleText healthTxt;
      RectangleText nameTxt;

      // Setea el nuevo state del worm
      void setState(view_worm_state_t);

    public:
      Worm(SDL_Renderer *, std::string, size_t, int);
      virtual ~Worm(void);
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      std::string getName(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
      void updateState(const YAML::Node &);
      void setProtagonic(bool);
      void setMirrored(bool);
      void setWalking(bool);
      void renderWormData(SDL_Renderer *, int, int);
      void setHealth(int);
      void setFalling(bool);
      void setGrounded(bool);
      void setAffectedByExplosion(bool);
      void setSightAngle(int);
      void setDataConfiguration(worm_data_cfg_t);
      int getHealth(void);
      bool isAlive(void);
      bool isAffectedByExplosion(void);
  };
}

#endif
