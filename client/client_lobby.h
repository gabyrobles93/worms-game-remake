#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QWidget>
#include <string>
#include "socket.h"
#include "socket_error.h"
#include "protocol.h"

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
    std::string player_name;
    
    void introduceToServer(void);
    void connectEvents(void);
    void exitLobby(void);

};

#endif // CLIENT_LOBBY_H
