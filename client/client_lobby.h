#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QWidget>
#include "socket.h"
#include "socket_error.h"

namespace Ui {
class client_lobby;
}

class client_lobby : public QWidget
{
    Q_OBJECT

public:
    explicit client_lobby(QWidget *parent = 0);
    SocketReadWrite * skt;
    ~client_lobby();

private:
    Ui::client_lobby *ui;
};

#endif // CLIENT_LOBBY_H
