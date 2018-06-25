#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <qt5/QtWidgets/QMessageBox>
#include <fstream>
#include <string>
#include <sstream>
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
#include "client_settings.h"

#define TIE_GAME_CODE 0
#define CONSTANT_WAIT 100/6
#define MAX_QUEUE_MODELS 256
#define MAP_RECEIVED_NAME "/usr/etc/worms/temp/map.tar.gz"
#define MAP_YML_PATH "/usr/etc/worms/temp/map.yml"

extern ClientSettings gClientSettings;

ClientGame::ClientGame(Protocol * prt, size_t tid) :
protocol(prt),
events(MAX_QUEUE_MODELS),
team_id(tid) {
	std::string map_received_name(MAP_RECEIVED_NAME);
	std::fstream file_map("tmp/temp_map_folder " + map_received_name, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	std::cout << "Esperando mapa del sevidor." << std::endl;
    this->protocol->rcvFile(file_map);
	std::cout << "Mapa recibido del servidor." << std::endl;
	file_map.close();
	std::string cmd_unzip_tar_gz = "tar -xf " + map_received_name + " -C /usr/etc/worms/temp";
	std::system(cmd_unzip_tar_gz.c_str());
	this->mapNode = YAML::LoadFile(MAP_YML_PATH);
	this->creator = false;
}

ClientGame::~ClientGame(void) {
	removeTempFiles();
}

ClientGame::ClientGame(Protocol * prt, size_t tid, std::string & mp) :
protocol(prt),
events(MAX_QUEUE_MODELS),
team_id(tid) {
	std::cout << "La ruta del mapa es " << mp << std::endl;
	std::string cmd_unzip_tar_gz = "tar -xf " + mp + " -C /usr/etc/worms/temp";
	std::system(cmd_unzip_tar_gz.c_str());
	this->mapNode = YAML::LoadFile(MAP_YML_PATH);
	this->creator = true;
}

void ClientGame::removeTempFiles(void) {
	if (!this->creator) {
		std::string map_received_name(MAP_RECEIVED_NAME);
		std::string cmd_rm_map_yml = "rm /usr/etc/worms/temp/map.yml /usr/etc/worms/temp/background.png " + map_received_name;
		std::system(cmd_rm_map_yml.c_str());
	} else {
		std::string cmd_rm_map_yml = "rm /usr/etc/worms/temp/map.yml /usr/etc/worms/temp/background.png";
		std::system(cmd_rm_map_yml.c_str());		
	}
}

void ClientGame::startGame(void) {
	EventSender event_sender(this->protocol, events);
	YAML::Node staticMap = this->mapNode["static"];
	YAML::Node dynamicMap = this->mapNode["dynamic"];
	YAML::Node wormsNode = dynamicMap["worms_teams"];

	ProtectedDynamics pdynamics(dynamicMap);
	ModelReceiver model_receiver(this->protocol, pdynamics);

	// Creo la pantalla con dichas cosas estáticas.
	View::WindowGame mainWindow(staticMap, gClientSettings.RESOLUTION_WIDTH, 
	gClientSettings.RESOLUTION_HIGH, gClientSettings.FULL_SCREEN);
	SDL_Renderer * renderer = mainWindow.getRenderer();
	View::Camera camera(mainWindow.getScreenWidth(), mainWindow.getScreenHeight(),
						mainWindow.getBgWidth(), mainWindow.getBgHeight());

	ClientConfiguration cfg(
		renderer, 
		mainWindow.getScreenWidth(), 
		mainWindow.getScreenHeight(),
		staticMap, 
		this->team_id
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

	model_receiver.stop();
	model_receiver.join();

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
	bool defeated_msg_showed = false;

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

				camera.handleEvent(e);
			}
		}

		camera.updateCameraPosition();
		
		const View::Projectil * projectilProtagonic = projectiles.getProjectilProtagonic();
		const View::Worm * protagonicWorm = worms.getWormView(cfg.getWormProtagonicId());
		const View::Worm * wormAffectedByExplosion = worms.getWormAffectedByExplosion();
		if (wormAffectedByExplosion) {
			camera.focus(*wormAffectedByExplosion);
		}else if (projectilProtagonic) {
			camera.focus(*projectilProtagonic);
		} else if (protagonicWorm) {
			camera.focus(*protagonicWorm);
		}

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
			size_t team_winner = pdynamics.getWinnerTeam();
			if (team_winner == this->team_id) {
				QMessageBox msgBox;
				msgBox.setWindowTitle("Ganaste.");
				msgBox.setText("Sos el rey de los gusanos!");
				msgBox.exec();				
			} else if (team_winner == TIE_GAME_CODE) {
				QMessageBox msgBox;
				msgBox.setWindowTitle("Empate.");
				msgBox.setText("Fue una partida muy reñida!");
				msgBox.exec();					
			} else {
				QMessageBox msgBox;
				msgBox.setWindowTitle("Partida terminada.");
				msgBox.setText("Terminó la partida. Una pena que hayas perdido.");
				msgBox.exec();					
			}
			return;
		}

		renderCount++;
		
		if (pdynamics.hasGameStatus()) {
			cfg.update(pdynamics.getGameStatus(), pdynamics.getTeamInventory(this->team_id));
			worms.updateWormsClientConfiguration(cfg);
			if (!defeated_msg_showed && pdynamics.teamDefeated(this->team_id)) {
				QMessageBox msgBox;
				msgBox.setWindowTitle("Perdiste.");
				msgBox.setText("Tu equipo ha perdido. ¡Más suerte la próxima!");
				msgBox.exec();
				defeated_msg_showed = true;
			}
		}

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
			timeLostSleeping = SDL_GetTicks() - (tf + to_sleep);
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
