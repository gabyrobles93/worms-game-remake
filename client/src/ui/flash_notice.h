#ifndef __FLASH_NOTICE_H__
#define __FLASH_NOTICE_H__

#include <SDL2/SDL.h>
#include <string>
#include "rectangle_text.h"
#include "sdl_timer.h"

class FlashNotice {
  private:
    View::RectangleText notice;
    int screenWidth;
    int screenHeight;
    Timer timer;

  public:
    FlashNotice(void);
    FlashNotice(int sw, int sh, int percentWindow = 4);
    ~FlashNotice();
    void render(SDL_Renderer *);
    void showFlashNotice(SDL_Renderer *, const std::string &);
    void setScreenWidth(int);
    void setScreenHeight(int);
};

#endif