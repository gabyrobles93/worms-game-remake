#ifndef __LOBBY_ATTENDANT_H__
#define __LOBBY_ATTENDANT_H__

#include <map>
#include <string>
#include "thread.h"
#include "client.h"
#include "event.h"
#include "waiting_game.h"
#include "protected_waiting_games.h"

class LobbyAttendant : public Thread {
    private:
        Client * client;
        ProtectedWaitingGames & waiting_games;
        bool keep_running;
        std::string player_name;

        size_t getId(void) const;
        void processEvent(Event &);
        void refreshLobby(void);
        void createMatch(std::string &, size_t);
        void removeWaitingMatch(void);
        void joinWaitingMatch(std::string &);
        void exitWaitingMatch(void);
        void refreshWaitingList(void);
        void startMatch(void);

    public:
        LobbyAttendant(Client *, ProtectedWaitingGames &);
        bool isRunning(void) const;
        virtual void run(void);
        void stop(void);
};

#endif