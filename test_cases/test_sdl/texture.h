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

      // Desaloca memoria
      void free();

    public:
      //Initializes variables
      Texture();

      //Deallocates memory
      ~Texture();

      // Carga la imagen desde un archivo
      void loadFromFile(std::string path, SDL_Renderer *);		

      // Renderiza la textura en toda la pantalla
      void render(SDL_Renderer *);
      // Render textura a un punto dado
      virtual void render(SDL_Renderer *, int, int);
      // Para poder renderizar texturas espejadas o rotadas
		  void render(SDL_Renderer *, int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

      // Dimensiones de la imagen
      virtual int getWidth(void) const;
      virtual int getHeight(void) const;

      // Posiciones de la imagen
      virtual int getX(void) const;
      virtual int getY(void) const;

      // Seteo de posiciones de la imagen
      virtual void setX(int);
      virtual void setY(int);
  };
}

#endif
