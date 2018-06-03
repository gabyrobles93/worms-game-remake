#include <iostream>
#include <QApplication>
#include "editor_launcher.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "window_game.h"
#include "girder_long.h"
#include "paths.h"
#include "girder_short.h"
#include "inventory.h"
#include "inventory_editor.h"
#include "inventory_weapons.h"
#include "map_game.h"
#include "worm.h"
#include "yaml.h"

#define ARGC_DEFAULT 1
#define ARGC_FILE_CONFIG 2

// Variable global
Paths gPath;

void validateArgs(int, char*[], YAML::Node & map);

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    EditorLauncher w;
    w.show();

    return a.exec();
}
