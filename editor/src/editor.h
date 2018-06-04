#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <SDL2/SDL.h>
#include <string>
#include "map_game.h"
#include "window_game.h"
#include "yaml.h"
#include "inventory.h"
#include "inventory_editor.h"

class Editor {
    private:
        std::string bg_name;
        std::string map_name;
        YAML::Node mapNode;
        YAML::Node staticNode;
        View::MapGame mapGame;
        View::WindowGame editorWindow;
        View::Camera camera;
        SDL_Renderer * renderer;
        View::EditorInventory editorInventory;
        int teamsAmount;
        int wormsHealth;
        bool validMap;

    public:
        Editor(YAML::Node, std::string, std::string);
        int start(void);
};

#endif