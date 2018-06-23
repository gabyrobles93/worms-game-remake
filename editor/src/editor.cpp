#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "editor.h"
#include "yaml.h"
#include "map_game.h"
#include "yaml.h"
#include "inventory.h"
#include "inventory_editor.h"

#define SAVE_PADDING 10
#define SAVE_ICON_SIDE 60

Editor::Editor(YAML::Node map, std::string mn, std::string bgn) :
bg_name(bgn),
map_name(mn),
mapNode(YAML::Clone(map)),
staticNode(mapNode["static"]),
mapGame(mapNode),
editorWindow(staticNode, 0, 0, true),
camera(editorWindow.getScreenWidth(),
        editorWindow.getScreenHeight(),
        editorWindow.getBgWidth(),
        editorWindow.getBgHeight()),
renderer(editorWindow.getRenderer()),
editorInventory(renderer,
             mapNode["static"]["teams_amount"].as<int>(),
             mapNode["static"]["worms_health"].as<int>()) {
	this->teamsAmount = mapNode["static"]["teams_amount"].as<int>();
	this->wormsHealth = mapNode["static"]["worms_health"].as<int>();
  this->editorInventory.toggleOpen();
	this->mapGame.setRenderer(this->renderer);
	this->saveTexture.loadFromFile(gPath.PATH_SAVE_ICON, this->renderer);
	this->saveTexture.setX(this->editorWindow.getScreenWidth() - SAVE_PADDING - SAVE_ICON_SIDE);
	this->saveTexture.setY(SAVE_PADDING); 
}

int Editor::start(void) {
    bool quit = false;
	SDL_Event e;
	int countclicks = 1;
	while (!quit) {
		int camX = camera.getX(), camY = camera.getY();
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				editorWindow.hide();
				validMap = mapGame.hasWorms();
				if (!validMap) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Mapa inválido.");
                    msgBox.setText("El mapa debe tener al menos un worm de cada team." "¿Desea continuar editando el mapa?");
                    msgBox.setStandardButtons(QMessageBox::Yes);
                    msgBox.addButton(QMessageBox::No);
                    msgBox.setDefaultButton(QMessageBox::Yes);
                    if(msgBox.exec() == QMessageBox::Yes) {
                        editorWindow.show();
						quit = false;
                    }
				}
			}

			if (e.type == SDL_KEYDOWN) {
				
					if (e.key.keysym.sym == SDLK_z && (e.key.keysym.mod & KMOD_CTRL)) {
						mapGame.setPreviousState(editorInventory);
					}
					
					if (e.key.keysym.sym == SDLK_y && (e.key.keysym.mod & KMOD_CTRL)) {
						mapGame.setNextState(editorInventory);
					}
				
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int mouseX, mouseY;
  			SDL_GetMouseState(&mouseX, &mouseY);
				if (e.button.button == SDL_BUTTON_LEFT) {
					if (mouseX > this->saveTexture.getX() && mouseX < this->saveTexture.getX() + SAVE_ICON_SIDE) {
						if (mouseY > this->saveTexture.getY() && mouseY < this->saveTexture.getY() + SAVE_ICON_SIDE) {
							this->editorWindow.hide();
							std::cout << "You click save button " << countclicks++ << " times !!!" << std::endl;
							this->editorWindow.show();
						}
					} else {
						editorInventory.handleEvent(renderer, e, mapGame, camX, camY);
					}
				}
			} else {
				editorInventory.handleEvent(renderer, e, mapGame, camX, camY);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		camera.updateCameraPosition();

		editorWindow.render(camera);

		mapGame.render(renderer, camX, camY);
		
		editorInventory.renderSelectedInMouse(renderer);

		editorWindow.renderWater(camera);

		editorInventory.render(renderer);

		this->saveTexture.render(this->renderer, this->saveTexture.getX(), this->saveTexture.getY(), SAVE_ICON_SIDE, SAVE_ICON_SIDE);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(50); // Para no usar al mango el CPU
	}

	if (validMap) {
		QMessageBox msgBox;
		msgBox.setWindowTitle("Fin de edición");
		msgBox.setText("¿Desea guardar el mapa?");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.addButton(QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);
		if(msgBox.exec() == QMessageBox::Yes) {
			mapGame.saveAs(this->map_name, this->bg_name);
			return 0;
		}
	}

	return -1;
}
