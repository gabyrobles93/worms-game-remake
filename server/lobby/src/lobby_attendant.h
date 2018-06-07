#ifndef __LOBBY_ATTENDANT_H__
#define __LOBBY_ATTENDANT_H__

#include "thread.h"
#include "client.h"
#include "protected_matchs_status.h"
#include "event.h"

class LobbyAttendant : public Thread {
    private:
        Client * client;
        ProtectedMatchsStatus & matchs_status;
        bool keep_running;

        size_t getId(void) const;
        void processEvent(Event &);

    public:
        LobbyAttendant(Client *, ProtectedMatchsStatus &);
        bool isRunning(void) const;
        virtual void run(void);
        void stop(void);
};

#endif