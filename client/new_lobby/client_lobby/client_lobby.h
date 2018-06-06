#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QMainWindow>

namespace Ui {
class ClientLobby;
}

class ClientLobby : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientLobby(QWidget *parent = 0);
    ~ClientLobby();

private:
    Ui::ClientLobby *ui;
};

#endif // CLIENT_LOBBY_H
