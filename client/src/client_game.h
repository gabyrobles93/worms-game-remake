#ifndef __CLIENT_GAME_H__
#define __CLIENT_GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "protocol.h"
#include "blocking_queue.h"
#include "event_sender.h"
#include "camera.h"
#include "window_game.h"
#include "worms_status.h"
#include "protected_dynamics.h"
#include <string>

class ClientGame {
    private:
        Protocol * protocol;
        Queue<Event> events;
        size_t team_id;
        YAML::Node mapNode;
        bool creator;

        void removeTempFiles(void);

    public:
        ClientGame(Protocol *, size_t, std::string &);
        ClientGame(Protocol *, size_t);
        ~ClientGame(void);
        void startGame(void);
        void gameLoop(View::Camera &, View::WindowGame &, SDL_Renderer *, ProtectedDynamics &, View::WormsStatus &, ClientConfiguration &);
};

#endif