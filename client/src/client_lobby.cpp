#include <iostream>
#include <sstream>
#include <fstream>
#include <QtGui/QCloseEvent>
#include <qt5/QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QTableWidget>
#include "QStackedWidget"
#include "client_lobby.h"
#include "ui_clientlobby.h"
#include "socket.h"
#include "socket_error.h"
#include "event.h"
#include "types.h"
#include "waiting_match.h"
#include "client_game.h"
#include "client_settings.h"

#define PAGE_CONNECTION_INDEX 0
#define PAGE_LOBBY_INDEX 1
#define PAGE_MATCH_CREATE 2
#define PAGE_WAITING_MATCH_INDEX 3
#define PAGE_JOINED_WAITING_MATCH_INDEX 4
#define PAGE_SETTINGS 6
#define PAGE_ABOUT 5

extern ClientSettings gClientSettings;

ClientLobby::ClientLobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientLobby)
{
    ui->setupUi(this);
    connectEvents();
    this->pages = findChild<QStackedWidget*>(WIDGET_PAGES);
    this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
    this->protocol = nullptr;
    this->waiting_match = nullptr;
    this->connected = false;
}

ClientLobby::~ClientLobby()
{
    cleanLobby();
    if (this->protocol != nullptr) {
        delete this->protocol;
    }
    delete ui;
}

void ClientLobby::connectEvents(void) {
    QPushButton* cleanTextBoxes = findChild<QPushButton*>(WIDGET_BUTTON_CLEAN_LOGIN);
    QObject::connect(cleanTextBoxes, &QPushButton::clicked,
                     this, &ClientLobby::cleanTextBoxes);

    QPushButton* connectButton = findChild<QPushButton*>(WIDGET_BUTTON_CONNECT_LOGIN);
    QObject::connect(connectButton, &QPushButton::clicked,
                     this, &ClientLobby::connectToServer);

    QPushButton* createButton = findChild<QPushButton*>(WIDGET_BUTTON_CREATE_GAME);
    QObject::connect(createButton, &QPushButton::clicked,
                     this, &ClientLobby::createMatch);

    QPushButton* exitLobbyButton = findChild<QPushButton*>(WIDGET_BUTTON_EXIT_LOBBY);
    QObject::connect(exitLobbyButton, &QPushButton::clicked,
                     this, &ClientLobby::exitLobby);

    QPushButton* joinButton = findChild<QPushButton*>(WIDGET_BUTTON_JOIN_GAME);
    QObject::connect(joinButton, &QPushButton::clicked,
                     this, &ClientLobby::joinMatch);

    QPushButton* refreshButton = findChild<QPushButton*>(WIDGET_BUTTON_REFRESH_LOBBY);
    QObject::connect(refreshButton, &QPushButton::clicked,
                     this, &ClientLobby::refreshLobby);

    QPushButton* createGameButton = findChild<QPushButton*>(WIDGET_BUTTON_START_WAITING_MATCH);
    QObject::connect(createGameButton, &QPushButton::clicked,
                     this, &ClientLobby::waitForPlayersOnCreatedMatch);

    QPushButton* backLobbyButton = findChild<QPushButton*>(WIDGET_BUTTON_BACK_TO_LOBBY);
    QObject::connect(backLobbyButton, &QPushButton::clicked,
                     this, &ClientLobby::backLobby);

    QPushButton* chooseMapsFolderButton = findChild<QPushButton*>(WIDGET_BUTTON_CHOOSE_MAP);
    QObject::connect(chooseMapsFolderButton, &QPushButton::clicked,
                     this, &ClientLobby::chooseMap);

    QPushButton* refreshWaitingPlayersButton = findChild<QPushButton*>(WIDGET_BUTTON_REFRESH_WAITING_PLAYERS);
    QObject::connect(refreshWaitingPlayersButton, &QPushButton::clicked,
                     this, &ClientLobby::feedWaitingPlayers);;

    QPushButton* startWaitingMatchButton = findChild<QPushButton*>(WIDGET_BUTTON_START_MATCH);
    QObject::connect(startWaitingMatchButton, &QPushButton::clicked,
                     this, &ClientLobby::startWaitingMatch);

    QPushButton* cancelWaitingMatchButton = findChild<QPushButton*>(WIDGET_BUTTON_CANCEL_WAITING_MATCH);
    QObject::connect(cancelWaitingMatchButton, &QPushButton::clicked,
                     this, &ClientLobby::cancelWaitingMatch);

    QPushButton* exitWaitingMatchButton = findChild<QPushButton*>(WIDGET_BUTTON_EXIT_WAITING_MATCH);
    QObject::connect(exitWaitingMatchButton, &QPushButton::clicked,
                     this, &ClientLobby::exitWaitingMatch);

    QAction* preferences = findChild<QAction*>("actionPreferencias");
    QObject::connect(preferences, &QAction::triggered, this, &ClientLobby::showPreferences);

    QAction* about = findChild<QAction*>("actionAcerca_de");
    QObject::connect(about, &QAction::triggered, this, &ClientLobby::showAbout);

    QPushButton* saveSettings = findChild<QPushButton*>(WIDGET_BUTTON_SAVE_SETTINGS);
    QObject::connect(saveSettings, &QPushButton::clicked,
                     this, &ClientLobby::saveSettingsAndBack);

    QPushButton* backAbout = findChild<QPushButton*>("button_back_about");
    QObject::connect(backAbout, &QPushButton::clicked,
                     this, &ClientLobby::backFromAbout);

}

void ClientLobby::cleanTextBoxes(void) {
    /* std::cout << "Clear Text." << std::endl; */
    QLineEdit* playerNameText = findChild<QLineEdit*>(WIDGET_TEXT_PLAYER_NAME);
    playerNameText->clear();
    QLineEdit* ipText = findChild<QLineEdit*>(WIDGET_TEXT_IP);
    ipText->clear();
    QLineEdit* portText = findChild<QLineEdit*>(WIDGET_TEXT_PORT);
    portText->clear();
}

void ClientLobby::connectToServer(void) {
    QLineEdit* ipText = findChild<QLineEdit*>(WIDGET_TEXT_IP);
    QLineEdit* portText = findChild<QLineEdit*>(WIDGET_TEXT_PORT);
    QLineEdit* pnameText = findChild<QLineEdit*>(WIDGET_TEXT_PLAYER_NAME);
    if (ipText->text().isEmpty() || portText->text().isEmpty() || pnameText->text().isEmpty()) {
        return;
    }
    std::string ip = ipText->displayText().toUtf8().constData();
    std::string port = portText->displayText().toUtf8().constData();
    this->player_name = pnameText->displayText().toUtf8().constData();
    /* std::cout << "El usuario intenta conectarse a " << ip << ":" << port << std::endl; */

    try {
        SocketConnection skt(ip, port);
        this->protocol = new Protocol(std::move(skt));
        /* std::cout << "Socket creado para conexión con servidor " << skt.sockfd << std::endl; */
    } catch (const SocketError & e) {
        std::cout << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error de conexión.");
        msgBox.setText("No se pudo conectar con el servidor. Por favor, chequee ip y puerto.");
        msgBox.exec();
        return;
    }
    /* std::cout << "Conexion con servidor establecida" << std::endl; */

    this->connected = true;
    goLobby();
}

void ClientLobby::goLobby(void) {
    this->protocol->sendName(this->player_name);
    // Recibe el nuevo nombre (si hubo colisión) que le asigna el servidor.
    this->protocol->getPlayerName(this->player_name);
    /* std::cout << "El servidor me bautizó como: " << this->player_name << std::endl; */
    QLabel* playerName = findChild<QLabel*>(WIDGET_TEXT_PLAYER_NAME_LOBBY);
    playerName->setText(this->player_name.c_str());

    this->pages->setCurrentIndex(PAGE_LOBBY_INDEX);

    feedLobby();
}

void ClientLobby::createMatch(void) {
    this->pages->setCurrentIndex(PAGE_MATCH_CREATE);
}

void ClientLobby::exitLobby(void) {
    /* std::cout << "Me voy del lobby" << std::endl; */
    cleanLobby();
    this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
    Event new_event(a_quitLobby, 1);
    this->protocol->sendEvent(new_event);
    delete this->protocol;
    this->protocol = nullptr;
    this->connected = false;
}

void ClientLobby::joinMatch(void) {
    /* std::cout << "Me uno a una partida!" << std::endl; */
    QTableWidget * matchsList = findChild<QTableWidget*>(WIDGET_GAMES_TABLE);
    int index_selected = matchsList->selectionModel()->currentIndex().row();

    if (index_selected < 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Seleccione una partida.");
        msgBox.setText("Por favor, seleccione una partida de la lista.");
        msgBox.exec();
        return;
    }

    std::string match_creator_name;
    match_creator_name = matchsList->item(index_selected,1)->text().toUtf8().constData();
   /*  std::cout << "El creador de la partida a joinearse es: " << match_creator_name << std::endl; */

    Event new_event(a_joinWaitingMatch, match_creator_name);
    this->protocol->sendEvent(new_event);
    
    YAML::Node join_match_response;
    this->protocol->rcvMsg(join_match_response);
    if (join_match_response["code"].as<int>() == 0) {
        refreshLobby();
        /* std::cout << "La partida esta llena, no se puede acceder." << std::endl; */
        std::string msg = join_match_response["msg"].as<std::string>();
        QMessageBox msgBox;
        msgBox.setWindowTitle("No se puede unir a partida:");
        msgBox.setText(msg.c_str());
        msgBox.exec();
        return;
    } else if (join_match_response["code"].as<int>() == 1) {
        /* std::cout << "Hay lugar en la partida, accediendo!." << std::endl; */
        this->pages->setCurrentIndex(PAGE_JOINED_WAITING_MATCH_INDEX);
        QLabel* gameCreator = findChild<QLabel*>(WIDGET_TEXT_GAME_CREATOR);
        gameCreator->setText(match_creator_name.c_str());

        this->waiting_match = new WaitingMatch(this->protocol, this->pages);
        this->waiting_match->start();

    }
}

void ClientLobby::refreshLobby(void) {
    /* std::cout << "Refresh del lobby" << std::endl; */
    cleanLobby();
    /* std::cout << "Lobby limpiado" << std::endl; */
    Event new_event(a_refreshLobby, 1);
    this->protocol->sendEvent(new_event);
    feedLobby();
}

void ClientLobby::waitForPlayersOnCreatedMatch(void) {
    QLineEdit * matchName = findChild<QLineEdit*>(WIDGET_TEXT_GAME_NAME);
    std::string matchNameStr = matchName->text().toUtf8().constData();

    if (matchName->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Partida inválida.");
        msgBox.setText("Por favor, ingrese un nombre a la partida.");
        msgBox.exec();
        return;
    }

    if (this->map_game_path.size() <= 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Partida inválida.");
        msgBox.setText("Por favor, seleccione un mapa de la lista.");
        msgBox.exec();
        return;  
    }

    /* std::cout << "Lanzo una partida en espera!" << std::endl; */
    this->pages->setCurrentIndex(PAGE_WAITING_MATCH_INDEX);
    Event new_event(a_createMatch, matchNameStr, this->map_players_qty);
    this->protocol->sendEvent(new_event);
}

void ClientLobby::backLobby(void) {
    this->pages->setCurrentIndex(PAGE_LOBBY_INDEX);
    QLabel* currentMapPath = findChild<QLabel*>(WIDGET_TEXT_CHOOSED_MAP);
    currentMapPath->setText("Not selected. Please, choose a map!");
    this->map_game_path.clear();
    refreshLobby();
}

void ClientLobby::cleanLobby(void) {
    QTableWidget * matchsList = findChild<QTableWidget*>(WIDGET_GAMES_TABLE);
    while (matchsList->rowCount() > 0) {
        matchsList->removeRow(0);
    }
}

void ClientLobby::feedLobby(void) {
    /* std::cout << "Alimentando lobby!" << std::endl; */
    QTableWidget * matchsList = findChild<QTableWidget*>(WIDGET_GAMES_TABLE);
    YAML::Node gameStatus;
    this->protocol->rcvGameStatus(gameStatus);

    std::stringstream ss;
    ss << gameStatus;
    std::cout << ss.str() << std::endl;



    YAML::Node::const_iterator it;
    for (it = gameStatus["waiting_games"].begin(); it != gameStatus["waiting_games"].end(); it++) {

        matchsList->insertRow(matchsList->rowCount());

        QTableWidgetItem * table_game_name = new QTableWidgetItem((*it)["match_name"].as<std::string>().c_str());
        table_game_name->setFlags(table_game_name->flags() ^ Qt::ItemIsEditable);
        matchsList->setItem(matchsList->rowCount()-1, 0, table_game_name);

        QTableWidgetItem * table_game_creator = new QTableWidgetItem((*it)["creator"].as<std::string>().c_str());
        table_game_creator->setFlags(table_game_creator->flags() ^ Qt::ItemIsEditable);
        matchsList->setItem(matchsList->rowCount()-1, 1, table_game_creator);
        
        QTableWidgetItem * table_actual_players = new QTableWidgetItem((*it)["joined_players"].as<std::string>().c_str());
        table_actual_players->setFlags(table_actual_players->flags() ^ Qt::ItemIsEditable);
        matchsList->setItem(matchsList->rowCount()-1, 2, table_actual_players);

        QTableWidgetItem * table_max_players = new QTableWidgetItem((*it)["required_players"].as<std::string>().c_str());
        table_max_players->setFlags(table_max_players->flags() ^ Qt::ItemIsEditable);
        matchsList->setItem(matchsList->rowCount()-1, 3, table_max_players);
    }
}

void ClientLobby::chooseMap(void) {
    QString map_path;
    map_path = QFileDialog::getOpenFileName(this, tr("Choose a map"), "/usr/etc/worms/maps", tr("Tar gzipped (*.tar.gz)"));
    if (map_path.length() > 0) {
        this->map_game_path = map_path.toUtf8().constData();
        /* std::cout << "El mapa elegido es " << this->map_game_path << std::endl; */
        QLabel* currentMapPath = findChild<QLabel*>(WIDGET_TEXT_CHOOSED_MAP);
        currentMapPath->setText(this->map_game_path.c_str());
        std::string cmd_mkdir = "mkdir temp_map_folder";
        std::string cmd_unzip = "tar -xvf \"" +  this->map_game_path + "\" -C ./temp_map_folder/";
        std::system(cmd_mkdir.c_str());
        std::system(cmd_unzip.c_str());
        YAML::Node mapNode = YAML::LoadFile("temp_map_folder/map.yml");
        this->map_players_qty = mapNode["dynamic"]["worms_teams"].size();
        std::string cmd_rm_temp_dir = "rm -fr ./temp_map_folder";
        std::system(cmd_rm_temp_dir.c_str());
    } else {
        /* std::cout << "No se eligio un mapa." << std::endl; */
    }
}

void ClientLobby::feedWaitingPlayers(void) {
    /* std::cout << "Alimento la lista de jugadores en espera." << std::endl; */
    Event new_event(a_refreshWaitingList);
    this->protocol->sendEvent(new_event);
    YAML::Node waiting_players_list;
    this->protocol->rcvMsg(waiting_players_list);

    std::stringstream ss;
    ss << waiting_players_list;
    std::cout << ss.str() << std::endl;

    QListWidget * waitingPlayersList = findChild<QListWidget*>(WIDGET_LIST_WAITING_PLAYERS);

    waitingPlayersList->clear();

    YAML::Node::const_iterator it;
    for (it = waiting_players_list["waiting_players"].begin(); it != waiting_players_list["waiting_players"].end(); it++) {
        std::string waiting_player_name = (*it).as<std::string>();
        if (waiting_player_name == this->player_name) continue;

        QListWidgetItem * new_list_widget = new QListWidgetItem;
        new_list_widget->setText(tr(waiting_player_name.c_str()));
        waitingPlayersList->insertItem(1, new_list_widget);    

    }
}

void ClientLobby::startWaitingMatch(void) {
    /* std::cout << "Comienzo juego" << std::endl; */
    Event new_event(a_startMatch);
    YAML::Node response;
    this->protocol->sendEvent(new_event);
    /* std::cout << "Esperando respuesta del server..." << std::endl; */
    this->protocol->rcvMsg(response);
    /* std::cout << "Respuesta del server recibida." << std::endl; */

    if (response["code"].as<int>() == 1) {
        /* std::cout << "El servidor me dio el OK para iniciar la partida."; */
        size_t team_id = response["team_id"].as<size_t>();
        /* std::cout << "Me asignó el team id " << team_id << std::endl; */
        std::fstream map_file(this->map_game_path, std::fstream::in | std::fstream::binary);
        this->protocol->sendFile(map_file);
        map_file.close();
        /* std::cout << "Aca instancio un juego cliente y lo lanzo pasandole el protocolo." << std::endl; */
        ClientGame the_game(this->protocol, team_id, this->map_game_path);
        the_game.startGame();
        backLobby();
    } else {
        /* std::cout << "La partida no puede comenzar" << std::endl; */
        feedWaitingPlayers();
        QMessageBox msgBox;
        msgBox.setWindowTitle("No se puede iniciar partida.");
        std::string msg_response = response["msg"].as<std::string>();
        msgBox.setText(msg_response.c_str());
        msgBox.exec();
    }
}

// Invocada cuando el CREADOR de una partida en espera cancela dicha partida...
void ClientLobby::cancelWaitingMatch(void) {
    /* std::cout << "Cancelo juego en espera." << std::endl; */
    Event new_event(a_rmWaitingMatch);
    this->protocol->sendEvent(new_event);
    backLobby();
}

// Invocada cuando un participante no-creador de una partida en espera se va de dicha partida en espera
void ClientLobby::exitWaitingMatch(void) {
    /* std::cout << "Me voy de una waiting match siendo un invitado." << std::endl; */
    if (this->waiting_match->isRunning()) {
        Event new_event(a_exitWaitingMatch);
        this->protocol->sendEvent(new_event);
    }
    this->waiting_match->stop();
    this->waiting_match->join();
    delete this->waiting_match;
    this->waiting_match = nullptr;
    backLobby();
}

void ClientLobby::closeEvent(QCloseEvent * event) {
    if (this->waiting_match) {
        exitWaitingMatch();
    }
    if (this->protocol) {
        exitLobby();
    }
    std::cout << "Cerrando cliente." << std::endl;
}

void ClientLobby::showPreferences(void) {
    this->pages->setCurrentIndex(PAGE_SETTINGS);
}

void ClientLobby::showAbout(void) {
    this->pages->setCurrentIndex(PAGE_ABOUT);
}

void ClientLobby::saveSettingsAndBack(void) {
    QString resolution;
    resolution = findChild<QComboBox*>("combo_screen_resolution")->currentText();
    std::string str_resolution = resolution.toUtf8().constData();
    if (str_resolution == "800 x 600") {
        gClientSettings.RESOLUTION_WIDTH = 800;
        gClientSettings.RESOLUTION_HIGH = 600;
    } else if (str_resolution == "1024 x 768") {
        gClientSettings.RESOLUTION_WIDTH = 1024;
        gClientSettings.RESOLUTION_HIGH = 768;
    } else if (str_resolution == "1152 x 640") {
        gClientSettings.RESOLUTION_WIDTH = 1152;
        gClientSettings.RESOLUTION_HIGH = 640;        
    } else if (str_resolution == "1280 x 768") {
        gClientSettings.RESOLUTION_WIDTH = 1280;
        gClientSettings.RESOLUTION_HIGH = 768;        
    } else if (str_resolution == "1920 x 1080") {
        gClientSettings.RESOLUTION_WIDTH = 1920;
        gClientSettings.RESOLUTION_HIGH = 1080;        
    }

    if (findChild<QCheckBox*>("check_full_screen")->isChecked()) {
        gClientSettings.FULL_SCREEN = 1;
    } else {
        gClientSettings.FULL_SCREEN = 0;
    }

    if (findChild<QCheckBox*>("check_sound_fx")->isChecked()) {
        gClientSettings.SOUND_FX = 1;
    } else {
        gClientSettings.SOUND_FX = 0;
    }

    if (this->connected) {
        backLobby();
    } else {
        this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
    }
}

void ClientLobby::backFromAbout(void) {
    if (this->connected) {
        backLobby();
    } else {
        this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
    }
}