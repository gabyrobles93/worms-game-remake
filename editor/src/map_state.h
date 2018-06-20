#ifndef __MAP_STATE_H__
#define __MAP_STATE_H__

#include <map>
#include "girder_long.h"
#include "girder_short.h"
#include "worm.h"
#include <SDL2/SDL.h>

class MapState {
private:
    std::map<int, View::GirderShort*> shortGirders;
    std::map<int, View::GirderLong*> longGirders;
	std::map<std::size_t, std::vector<View::Worm*>> worms;
public:
    MapState();
    ~MapState();
    void render(SDL_Renderer* renderer, int camX, int camY);
    void operator=(MapState* mapState);
    std::map<int, View::GirderShort*> getShortGirders();
    std::map<int, View::GirderLong*> getLongGirders();
    std::map<std::size_t, std::vector<View::Worm*>> getWorms();
    void addShortGirder(SDL_Renderer* rendeder, degrees_t degrees, int x, int y);
    void addLongGirder(SDL_Renderer* renderer, degrees_t degrees, int x, int y);
    void addWorm(SDL_Renderer* renderer, int teamId, std::string & name, int health, int x, int y);
};

#endif