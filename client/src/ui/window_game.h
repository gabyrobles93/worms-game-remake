#ifndef __WINDOW_GAME_H__
#define __WINDOW_GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>
#include "girder_short.h"
#include "girder_long.h"
#include "camera.h"
#include "texture.h"
#include "water.h"
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
    
    YAML::Node & staticMap;
    Water water;

    // TODO: Crear clase background y encapsular esto
    View::Texture background;
    std::string backgroundDisplayMode;

    void init(void);
    bool loadMedia(void);
    void close(void);
    int getWidthResolution(void);
    int getHeightResolution(void);
    void loadStaticObjects(void);

  public:
    // Constructor para el cliente
    WindowGame(YAML::Node &, int w = 0, int h = 0);
    
    // Constructor para el editor de mapas
    WindowGame(std::string pathToBg, int waterLevel);
    ~WindowGame();
    SDL_Renderer * getRenderer(void) const;
    int getScreenWidth(void) const;
    int getScreenHeight(void) const;
    int getBgWidth(void) const;
    int getBgHeight(void) const;
    void render(View::Camera &);

    // El agua debe ser lo ultimo que se dibuja
    void renderWater(View::Camera &);

    // Renderiza el fondo. Se puede programar
    // para que sea en mosaico, centrado o expandido
    void renderBackground(View::Camera &);

    // Esconde la ventana
    void hide(void);

    // Muestra la ventana
    void show(void);
};

#endif
