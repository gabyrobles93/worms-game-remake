#ifndef __LOBBY_ATTENDANT_H__
#define __LOBBY_ATTENDANT_H__

#include <map>
#include <string>
#include "thread.h"
#include "client.h"
#include "protected_matchs_status.h"
#include "event.h"
#include "waiting_game.h"

class LobbyAttendant : public Thread {
    private:
        Client * client;
        ProtectedMatchsStatus & matchs_status;
        std::map<std::string, WaitingGame*> & waiting_games;
        bool keep_running;

        size_t getId(void) const;
        void processEvent(Event &);

    public:
        LobbyAttendant(Client *, ProtectedMatchsStatus &, std::map<std::string, WaitingGame*> &);
        bool isRunning(void) const;
        virtual void run(void);
        void stop(void);
};

#endif