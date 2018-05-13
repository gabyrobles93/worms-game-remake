#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QWidget>
#include <string>
#include <fstream>
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"
#include "client_lobby_feeder.h"

namespace Ui {
class client_lobby;
}

class client_lobby : public QWidget
{
    Q_OBJECT

public:
    explicit client_lobby(QWidget *parent, SocketReadWrite skt, std::string &);
    ~client_lobby(void);

private:
    Ui::client_lobby *ui;
    Protocol protocol;
    ClientLobbyFeeder feeder;
    std::string player_name;

    void introduceToServer(void);
    void connectEvents(void);
    void exitLobby(void);
};

#endif