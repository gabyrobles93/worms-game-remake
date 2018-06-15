#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>
#include "drawable.h"

namespace View {
  class Camera {
    private:
      SDL_Rect camera;

      // Dimensiones de la camara
      int width;
      int height;

      // Dimensiones del nivel
      int levelWidth;
      int levelHeight;

      bool movingLeft;
      bool movingRight;
      bool movingUp;
      bool movingDown;

    public:
      Camera(int camW, int camH, int levelW, int levelH);
      ~Camera();

      // Getters de la posicion de la camara
      int getX(void) const;
      int getY(void) const;

      // Getter del rectangulo de la camara
      SDL_Rect getCamera(void) const;

      // Seters de la posicion de la camara
      void setX(int);
      void setY(int);
      void setXY(int, int);

      // Centra la camara en un dibujable
      void focus(const Drawable &);

      // Mueve la camara si recibe el evento correspondiente
      void handleEvent(SDL_Event &);

      // Actualiza la posicion de la camara 
      // respecto de donde
      // esta ubicado el mouse
      void updateCameraPosition(void);
  };
}

#endif