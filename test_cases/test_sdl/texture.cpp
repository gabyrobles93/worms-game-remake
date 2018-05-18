#include "texture.h"

View::Texture::Texture() {
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
}

View::Texture::~Texture() {
	this->free();
}

void View::Texture::loadFromFile(std::string path, SDL_Renderer * renderer) {
	// Liberamos la textura actual
	this->free();

	// La textura final
	SDL_Texture* newTexture = NULL;

	// Cargamos la surface en el path indicado
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
    throw View::Exception("%s %s. %s: %s", ERR_MSG_LOAD_IMAGE, path.c_str(), "SDL_IMG_Load() ", IMG_GetError());
	} else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x80, 0x80, 0xBE));

		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
      throw View::Exception("%s %s. %s: %s", ERR_MSG_CREATE_TEXTURE, path.c_str(), "SDL_CreateTextureFromSurface() ", SDL_GetError());
		} else {
			// Cargamos las dimensiones de la imagen
			this->width = loadedSurface->w;
			this->height = loadedSurface->h;
		}
		// Liberamos la surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	this->texture = newTexture;
}

void View::Texture::free() {
	//Free texture if it exists
	if (this->texture != NULL) {
		SDL_DestroyTexture( this->texture );
		this->texture = NULL;
		this->width = 0;
		this->height = 0;
		this->x = 0;
		this->y = 0;
	}
}

void View::Texture::render(SDL_Renderer * renderer, int x, int y) {
	this->x = x;
	this->y = y;
	// Seteamos el espacio de dibujado y donde dibujarlo
	SDL_Rect renderQuad = { x, y, this->width, this->height };
	SDL_RenderCopy(renderer, this->texture, NULL, &renderQuad);
}

void View::Texture::render(SDL_Renderer * renderer) {
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
}

void View::Texture::render(
	SDL_Renderer * renderer, 
	int x, 
	int y, 
	SDL_Rect* clip, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip) {

	// Seteamos espacio de renderizado
	SDL_Rect renderQuad = { x, y, this->width, this->height };

	// Seteamos las dimensiones del clip
	if (clip)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Renderizamos al screen
	SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip );
}

int View::Texture::getWidth(void) {
	return this->width;
}

int View::Texture::getHeight(void) {
	return this->height;
}

int View::Texture::getX(void) {
	return this->x;
}

int View::Texture::getY(void) {
	return this->y;
}