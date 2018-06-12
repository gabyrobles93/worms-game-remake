#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include "client_game.h"
#include "protocol.h"
#include "event_sender.h"
#include "model_receiver.h"
#include "window_game.h"
#include "camera.h"
#include "socket.h"
#include "socket_error.h"
#include "protocol_error.h"
#include "blocking_queue.h"
#include "sdl_timer.h"
#include "client_configuration.h"
#include "types.h"
#include "yaml.h"
#include "worms_status.h"
#include "projectiles.h"
#include "inventory.h"

#define CONSTANT_WAIT 100/60
#define MAX_QUEUE_MODELS 256
#define MAP_RECEIVED_NAME "map.tar.gz"
#define MAP_YML_NAME "map.yml"
#define BACKGROUND_NAME "background.png"

ClientGame::ClientGame(Protocol * prt, size_t tid) :
protocol(prt),
events(MAX_QUEUE_MODELS),
team_id(tid) {
	removePreviousTempFiles();
	std::string map_received_name(MAP_RECEIVED_NAME);
	std::fstream file_map(map_received_name, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	std::cout << "Esperando mapa del sevidor." << std::endl;
    this->protocol->rcvFile(file_map);
	std::cout << "Mapa recibido del servidor." << std::endl;
	file_map.close();
	std::string cmd_unzip_tar_gz = "tar -xf " + map_received_name;
	std::system(cmd_unzip_tar_gz.c_str());
	this->mapNode = YAML::LoadFile(MAP_YML_NAME);
}

ClientGame::ClientGame(Protocol * prt, size_t tid, std::string & mp) :
protocol(prt),
events(MAX_QUEUE_MODELS),
team_id(tid) {
	removePreviousTempFiles();
	std::cout << "La ruta del mapa es " << mp << std::endl;
	std::string cmd_unzip_tar_gz = "tar -xf " + mp;
	std::system(cmd_unzip_tar_gz.c_str());
	this->mapNode = YAML::LoadFile(MAP_YML_NAME);
}

void ClientGame::removePreviousTempFiles(void) {
	std::string cmd_rm_map_yml = "rm map.yml background.png";
	std::system(cmd_rm_map_yml.c_str());
}

void ClientGame::startGame(void) {
	std::cout << "Start GAME!!" << std::endl;
	EventSender event_sender(this->protocol, events);
	YAML::Node staticMap = this->mapNode["static"];
	const YAML::Node & initInventory = staticMap["init_inventory"];
	YAML::Node dynamicMap = this->mapNode["dynamic"];
	YAML::Node wormsNode = dynamicMap["worms_teams"];

	ProtectedDynamics pdynamics(dynamicMap);
	ModelReceiver model_receiver(this->protocol, pdynamics);

	// Creo la pantalla con dichas cosas estáticas.
	View::WindowGame mainWindow(staticMap, 800, 600);
	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

	ClientConfiguration cfg(
		renderer, 
		mainWindow.getScreenWidth(), 
		mainWindow.getScreenHeight(),
		initInventory
	);

    View::WormsStatus worms(wormsNode, renderer);
	// Lanzo threads de enviar eventos y de recibir modelos
	event_sender.start();
	model_receiver.start();

	std::cout << "Iniciando game loop." << std::endl;
    gameLoop(camera, mainWindow, renderer, pdynamics, worms, cfg);
	std::cout << "Fin de game loop." << std::endl;

	// Salimos del ciclo del juego, enviamos evento de que nos fuimos.;

	Event event(a_quitGame, this->team_id);
	this->events.push(event);
	usleep(1000000);
	// Stop y Join de threads
	event_sender.stop();
	event_sender.join();
	std::cout << "Event Sender stopeado y joineado." << std::endl;
	model_receiver.stop();
	model_receiver.join();
	std::cout << "Model receiver stopeado y joineado." << std::endl;
}

void ClientGame::gameLoop(View::Camera & camera, View::WindowGame & mainWindow, SDL_Renderer * renderer, 
ProtectedDynamics & pdynamics, View::WormsStatus & worms, ClientConfiguration & cfg) try {
	bool quit = false;	
	SDL_Event e;
	int timeLostSleeping = 0;
	int ti; 
	int tf;
	int updateCount = 0;
	int renderCount = 0;

    View::Projectiles projectiles;
	bool match_finished = false;
	while (!quit && !match_finished) {
		ti = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			
			cfg.handleEvent(e);

			if (cfg.hasShooted()) {
				weapon_t weapon = cfg.getSelectedWeapon();
				if (weapon != w_air_strike && weapon != w_teleport) {
					Event event(a_shoot, weapon, this->team_id, cfg.getWeaponsCountdown(), cfg.getPowerShoot(), cfg.getSightAngle());
					this->events.push(event);
				} else {
					Event event(a_shoot, weapon, this->team_id, cfg.getRemoteControlX() + camera.getX(), cfg.getRemoteControlY() + camera.getY());
					this->events.push(event);
				}
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					Event event(a_pointUp, this->team_id);
					this->events.push(event);
				}
				if (e.key.keysym.sym == SDLK_s) {
					Event event(a_pointDown, this->team_id);
					this->events.push(event);
				}
				if (e.key.keysym.sym == SDLK_a) {
					Event event(a_moveLeft, this->team_id);
					this->events.push(event);
				}
				if (e.key.keysym.sym == SDLK_d) {
					Event event(a_moveRight, this->team_id);
					this->events.push(event);
				}
				if (e.key.keysym.sym == SDLK_RETURN) {
					Event event(a_frontJump, this->team_id);
					this->events.push(event);
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					Event event(a_backJump, this->team_id);
					this->events.push(event);
				}

				if (e.key.keysym.sym == SDLK_LEFT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_UP) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					camera.handleEvent(e);
				}
			}
		}

		camera.updateCameraPosition();

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		
		// Dibujamos cosas estáticas
		mainWindow.render(camera);

		// Procesamiento de los snapshoots
		bool thereIsModel = pdynamics.popModel();
		while (thereIsModel) {
			updateCount++;
			worms.update(pdynamics.getWorms());
			worms.updateWormProtagonic(pdynamics.getWormProtagonicId());
			projectiles.update(renderer, pdynamics.getProjectiles());
			thereIsModel = pdynamics.popModel();
			//std::cout << "Pop model " << ++i << std::endl;
		}
		//std::cout << "Render" << std::endl;
		match_finished  = pdynamics.finishedMatch();
		if (match_finished) {
			std::cout << "La partida terminóó." << std::endl;
			return;
		}

		renderCount++;
		cfg.update(pdynamics.getGameStatus(), pdynamics.getTeamInventory());
		worms.updateWormsClientConfiguration(cfg);

		// Dibujamos cosas dinámicas
		// Gusanos
		worms.render(renderer, camera);

		// Proyectiles
		projectiles.render(renderer, camera);

		// El agua va sobre todo menos el inventario
		mainWindow.renderWater(camera);

		// Dibujamos los objetos propios del cliente
		cfg.render(renderer);

		SDL_RenderPresent(renderer);
		tf = SDL_GetTicks();

		int to_sleep = CONSTANT_WAIT - (tf-ti) - timeLostSleeping;
		if (to_sleep < 0) {
			timeLostSleeping = 0;
		} else {
			SDL_Delay(to_sleep);
			timeLostSleeping = SDL_GetTicks() - (tf - to_sleep);
		}
	}

	std::cout << "Se termino el juego con" << std::endl;
	std::cout << "Renders count " << renderCount << std::endl;
	std::cout << "Updates count " << updateCount << std::endl;

} catch(const SocketError & e) {
	std::cout << e.what() << std::endl;
} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
}
