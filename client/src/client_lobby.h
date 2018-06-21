#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtGui/QCloseEvent>
#include "QStackedWidget"
#include "protocol.h"
#include "waiting_match.h"

#define WIDGET_PAGES "pages_client"
#define WIDGET_BUTTON_CLEAN_LOGIN "button_clean"
#define WIDGET_BUTTON_CONNECT_LOGIN "button_connect"
#define WIDGET_BUTTON_CREATE_GAME "button_create"
#define WIDGET_BUTTON_EXIT_LOBBY "button_exit_lobby"
#define WIDGET_BUTTON_JOIN_GAME "button_join"
#define WIDGET_BUTTON_REFRESH_LOBBY "button_refresh"
#define WIDGET_BUTTON_START_WAITING_MATCH "button_start"
#define WIDGET_BUTTON_BACK_TO_LOBBY "button_back_lobby"
#define WIDGET_BUTTON_CHOOSE_MAP "button_changue_maps_folder"
#define WIDGET_BUTTON_REFRESH_WAITING_PLAYERS "button_refresh_waiting_players"
#define WIDGET_BUTTON_START_MATCH "button_start_waiting_match"
#define WIDGET_BUTTON_CANCEL_WAITING_MATCH "button_cancel_waiting_match"
#define WIDGET_BUTTON_EXIT_WAITING_MATCH "button_exit_waiting_match"

#define WIDGET_TEXT_PLAYER_NAME "text_player_name"
#define WIDGET_TEXT_IP "text_ip"
#define WIDGET_TEXT_PORT "text_port"
#define WIDGET_TEXT_PLAYER_NAME_LOBBY "playerName"
#define WIDGET_TEXT_GAME_CREATOR "text_game_creator"
#define WIDGET_TEXT_GAME_NAME "text_game_name"
#define WIDGET_TEXT_CHOOSED_MAP "text_current_map_path"

#define WIDGET_LIST_WAITING_PLAYERS "list_waiting_players"

#define WIDGET_GAMES_TABLE "table_matchs"


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
    WaitingMatch * waiting_match;

    std::string map_game_path;
    int map_players_qty;

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
    void chooseMap(void);
    void feedWaitingPlayers(void);
    void startWaitingMatch(void);
    void cancelWaitingMatch(void);
    void exitWaitingMatch(void);
    void closeEvent(QCloseEvent *);
};

#endif
