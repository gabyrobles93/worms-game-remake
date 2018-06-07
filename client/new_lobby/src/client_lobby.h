#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "QStackedWidget"
#include "protocol.h"

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
    Protocol * protocol;
    std::string player_name;
    QList<QListWidgetItem*> lobby_games;
    QStackedWidget * pages;

    void connectEvents(void);
    void cleanTextBoxes(void);
    void connectToServer(void);
    void hideConnectionWindow(void);
    void showConnectionWindow(void);
    void goLobby(void);
    void createMatch(void);
    void exitLobby(void);
    void joinMatch(void);
    void refreshLobby(void);
    void feedLobby(void);
    void cleanLobby(void);
    void waitForPlayersOnCreatedMatch(void);
    void backLobby(void);
};

#endif // CLIENT_LOBBY_H
