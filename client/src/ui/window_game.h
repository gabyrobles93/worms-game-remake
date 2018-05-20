#ifndef __WINDOW_GAME_H__
#define __WINDOW_GAME_H__

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "girder_short.h"
#include "girder_long.h"
#include "camera.h"
#include "texture.h"
#include "yaml.h"

namespace View {
class WindowGame;
}

class View::WindowGame {
  private:
    SDL_Renderer * renderer;
    SDL_Window* window;
     // Vector de vigas creadas
    std::vector<View::GirderLong *> longGirders;
    std::vector<View::GirderShort *> shortGirders;
    int screen_width;
    int screen_height;
    View::Texture background;
    YAML::Node & staticMap;

    void init(void);
    bool loadMedia(void);
    void close(void);
    int getWidthResolution(void);
    int getHeightResolution(void);
    void loadStaticObjects(void);

  public:
    WindowGame(YAML::Node &, int w = 0, int h = 0);
    ~WindowGame();
    SDL_Renderer * getRenderer(void) const;
    int getScreenWidth(void) const;
    int getScreenHeight(void) const;
    int getBgWidth(void) const;
    int getBgHeight(void) const;
    void render(View::Camera &);
};

#endif
