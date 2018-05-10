#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



int main(int argc, char const *argv[]) {
	const int FPS = 60;
	int frameTime = 0;

	SDL_Window *window = nullptr;
	SDL_Texture *currentImage = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	SDL_Rect playerRect;
	SDL_Rect playerPosition;
	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 104;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ((!IMG_Init(imgFlags) & imgFlags))
		std::cout << "Error" << IMG_GetError() << std::endl;

	window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	currentImage = IMG_LoadTexture(renderTarget, "/home/gonza/Desktop/Box2D-SDL/wwinner.png");

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / 1;
	frameHeight = textureHeight / 14;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);
	bool isRunning = true;
	SDL_Event ev;

	Mix_Chunk *gMusic = NULL;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	gMusic = Mix_LoadWAV("/home/gonza/Desktop/Box2D-SDL/DRAGONPUNCH.WAV");

	Mix_PlayChannel(-1, gMusic, 0);
	while (isRunning) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) 
				isRunning = false;
		}

		frameTime++;

		if (FPS / frameTime == 20) {
			frameTime = 0;
			playerRect.y += frameHeight;
			if (playerRect.y >= textureHeight) {
				Mix_PlayChannel(-1, gMusic, 0);

				playerRect.y = 0;
			}
		}


		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playerPosition);
		SDL_RenderPresent(renderTarget);

	}

	Mix_FreeChunk(gMusic);
	gMusic = NULL;

	SDL_DestroyWindow(window);
	SDL_DestroyTexture(currentImage);
	SDL_DestroyRenderer(renderTarget);
	window = nullptr;
	currentImage = nullptr;
	renderTarget = nullptr;

	Mix_Quit();
	SDL_Quit();
}