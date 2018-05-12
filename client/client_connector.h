#ifndef CLIENT_CONNECTOR_H
#define CLIENT_CONNECTOR_H

#include <QMainWindow>
#include "socket.h"
#include "client_lobby.h"

namespace Ui {
class client_connector;
}

class client_connector : public QMainWindow
{
    Q_OBJECT

public:
    explicit client_connector(QWidget *parent = 0);
    ~client_connector();

private:
    Ui::client_connector *ui;
    SocketConnection *skt;
    client_lobby lobby;

    void connectEvents(void);
    void connectToServer(void);
};

#endif // CLIENT_CONNECTOR_H
