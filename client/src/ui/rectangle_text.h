#ifndef __RECTANGLE_TEXT_H__
#define __RECTANGLE_TEXT_H__

#include <SDL2/SDL.h>
#include <string>
#include "drawable.h"
#include "font.h"
#include "paths.h"
#include "texture.h"

#define DEFAULT_PADDING_RECTANGLE_TEXT 2

namespace View {
  class RectangleText: public Drawable {
    private:
      Texture text;
      Font font;
      SDL_Color textColor;
      SDL_Color backgroundColor;

      int padding;
      bool hide;
    public:
      RectangleText( 
        int h, 
        int padding = DEFAULT_PADDING_RECTANGLE_TEXT, 
        std::string path = gPath.PATH_FONT_ARIAL_BOLD
      );

      ~RectangleText();

      void setText(SDL_Renderer *, const std::string &);
      void setTextColor(SDL_Color &);
      void setBackgroundColor(SDL_Color &);
      void toggleHide(bool);

      virtual int getWidth(void) const;
      virtual int getHeight(void) const;
      virtual int getX(void) const;
      virtual int getY(void) const;
      virtual void setX(int);
      virtual void setY(int);
      virtual void render(SDL_Renderer *, int, int);
  };
}

#endif