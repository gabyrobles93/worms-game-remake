#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "view_exceptions.h"
#include "drawable.h"

namespace View {
  class Texture: public Drawable {
    private:
      // La textura actual
      SDL_Texture* texture;
      // Dimensiones
      int width;
      int height;

      // Desaloca memoria
      void free();

    public:
      //Initializes variables
      Texture();

      //Deallocates memory
      ~Texture();

      // Carga la imagen desde un archivo
      void loadFromFile(std::string path, SDL_Renderer *);		

      // Render textura a un punto dado
      virtual void render(SDL_Renderer *, int, int);

      // Dimensiones de la imaegen
      int getWidth(void);
      int getHeight(void);
  };
}

#endif
