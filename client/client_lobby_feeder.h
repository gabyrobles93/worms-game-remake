#ifndef __CLIENT_LOBBY_FEEDER_H__
#define __CLIENT_LOBBY_FEEDER_H__

#include <string>
#include <QTableWidget>
#include <fstream>
#include "protocol.h"
#include "thread.h"
#include "socket.h"

class ClientLobbyFeeder : public Thread {
    private:
        std::fstream games_status;
        Protocol & protocol;
        QTableWidget* games_table;
        bool running;
        
        bool isRunning(void) const;
        size_t getId(void) const;
        void feedGamesTable(void);
    public:
        ClientLobbyFeeder(Protocol &);
        ~ClientLobbyFeeder(void);
        void setGamesTable(QTableWidget*);
        virtual void run(void);
        void stop(void);
};

#endif