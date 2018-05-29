#ifndef __MAP_GAME_H__
#define __MAP_GAME_H__

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <string>
#include "girder_long.h"
#include "girder_short.h"
#include "inventory_editor.h"
#include "girder.h"
#include "worm.h"
#include "yaml.h"

namespace View {
  class EditorInventory;

  class MapGame {
    private:
      // Vector de estados de mapas
      // sirve tener los distintos estados
      // para agregar las funcionalidades de
      // deshacer y rehacer
      std::vector<YAML::Node *> mapStates;

      std::vector<View::GirderShort*> shortCollection;
	    std::vector<View::GirderLong*> longCollection;
	    std::map<std::size_t, std::vector<View::Worm*>> wormsCollection;

      size_t stateIndex;

      // Obtiene el id del proximo
      // worm a agregar del correspondiente
      // team id pasado por parametro
      int getNextWormId(int);

    public:
      // Constructor, recibe el nodo YAML
      // donde guardara toda la informacion del mapa
      MapGame(YAML::Node &);

      // Destructor, libera los items dibujados
      ~MapGame();

      // Dibuja lo que ya fue clickeado por el usuario
      void render(SDL_Renderer * r, int camX, int camY);

      // Agrega una short girder en la posicion del mapa indicada
      void addShortGirder(degrees_t, int, int);

      // Agrega una long girder en la posicion del mapa indicada
      void addLongGirder(degrees_t, int, int);

      // Agrega un worm
      void addWormInTeam(int, std::string &, int, int, int);

      // Establece el estado anterior (si hay)
      void setPreviousState(View::EditorInventory &);

      // Establece el estado posterior (si hay)
      void setNextState(View::EditorInventory &);

      // Imprime el estado actual
      void printCurrentState(void);

      // Actualiza el indice y libera los estados basura
      void updateIndex(void);
  };
}

#endif
