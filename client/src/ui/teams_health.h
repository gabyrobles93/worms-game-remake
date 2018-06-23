#ifndef __TEAMS_HEALTH_H__
#define __TEAMS_HEALTH_H__

#include <map>
#include "drawable.h"
#include "rectangle_text.h"
#include "paths.h"
#include "texture.h"
#include "yaml.h"


namespace View {
  class TeamsHealth: public Drawable {
    private:
      RectangleText text;
      int padding;
      int whiteTickness;
      int teamsAmount;
      int wormsHealth;
      int heightHealthRect;
      int maxTeamHealth;

      std::map<int, int> teamsHealth;
      bool hide;

    public:
      TeamsHealth(SDL_Renderer *, int, int, int, int, int);
      ~TeamsHealth();
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);

      void update(const YAML::Node &);
      void toggleHide(void);
  };
}

#endif