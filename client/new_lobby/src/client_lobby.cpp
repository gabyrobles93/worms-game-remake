#include <iostream>
#include <sstream>
#include <qt5/QtWidgets/QMessageBox>
#include <QFileDialog>
#include "QStackedWidget"
#include "client_lobby.h"
#include "ui_clientlobby.h"
#include "socket.h"
#include "socket_error.h"
#include "event.h"
#include "types.h"

#define DEFAULT_MAPS_FOLDER "../../../editor/maps"

#define PAGE_CONNECTION_INDEX 0
#define PAGE_LOBBY_INDEX 1
#define PAGE_MATCH_CREATE 2
#define PAGE_WAITING_MATCH_INDEX 3

ClientLobby::ClientLobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientLobby)
{
    ui->setupUi(this);
    connectEvents();
    this->pages = findChild<QStackedWidget*>("pages_client");
    this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
}

ClientLobby::~ClientLobby()
{
    cleanLobby();
    delete ui;
}

void ClientLobby::connectEvents(void) {
    QPushButton* cleanTextBoxes = findChild<QPushButton*>("button_clean");
    QObject::connect(cleanTextBoxes, &QPushButton::clicked,
                     this, &ClientLobby::cleanTextBoxes);

    QPushButton* connectButton = findChild<QPushButton*>("button_connect");
    QObject::connect(connectButton, &QPushButton::clicked,
                     this, &ClientLobby::connectToServer);

    QPushButton* createButton = findChild<QPushButton*>("button_create");
    QObject::connect(createButton, &QPushButton::clicked,
                     this, &ClientLobby::createMatch);

    QPushButton* exitLobbyButton = findChild<QPushButton*>("button_exit_lobby");
    QObject::connect(exitLobbyButton, &QPushButton::clicked,
                     this, &ClientLobby::exitLobby);

    QPushButton* joinButton = findChild<QPushButton*>("button_join");
    QObject::connect(joinButton, &QPushButton::clicked,
                     this, &ClientLobby::joinMatch);

    QPushButton* refreshButton = findChild<QPushButton*>("button_refresh");
    QObject::connect(refreshButton, &QPushButton::clicked,
                     this, &ClientLobby::refreshLobby);

    QPushButton* createGameButton = findChild<QPushButton*>("button_start");
    QObject::connect(createGameButton, &QPushButton::clicked,
                     this, &ClientLobby::waitForPlayersOnCreatedMatch);

    QPushButton* backLobbyButton = findChild<QPushButton*>("button_back_lobby");
    QObject::connect(backLobbyButton, &QPushButton::clicked,
                     this, &ClientLobby::backLobby);

    QPushButton* chooseMapsFolderButton = findChild<QPushButton*>("button_changue_maps_folder");
    QObject::connect(chooseMapsFolderButton, &QPushButton::clicked,
                     this, &ClientLobby::chooseMap);

    QPushButton* refreshWaitingPlayersButton = findChild<QPushButton*>("button_refresh_waiting_players");
    QObject::connect(refreshWaitingPlayersButton, &QPushButton::clicked,
                     this, &ClientLobby::feedWaitingPlayers);;

    QPushButton* startWaitingMatchButton = findChild<QPushButton*>("button_start_waiting_match");
    QObject::connect(startWaitingMatchButton, &QPushButton::clicked,
                     this, &ClientLobby::startWaitingMatch);

    QPushButton* cancelWaitingMatchButton = findChild<QPushButton*>("button_cancel_waiting_match");
    QObject::connect(cancelWaitingMatchButton, &QPushButton::clicked,
                     this, &ClientLobby::cancelWaitingMatch);
}

void ClientLobby::cleanTextBoxes(void) {
    std::cout << "Clear Text." << std::endl;
    QLineEdit* playerNameText = findChild<QLineEdit*>("text_player_name");
    playerNameText->clear();
    QLineEdit* ipText = findChild<QLineEdit*>("text_ip");
    ipText->clear();
    QLineEdit* portText = findChild<QLineEdit*>("text_port");
    portText->clear();
}

void ClientLobby::connectToServer(void) {
    QLineEdit* ipText = findChild<QLineEdit*>("text_ip");
    QLineEdit* portText = findChild<QLineEdit*>("text_port");
    QLineEdit* pnameText = findChild<QLineEdit*>("text_player_name");
    if (ipText->text().isEmpty() || portText->text().isEmpty() || pnameText->text().isEmpty()) {
        return;
    }
    std::string ip = ipText->displayText().toUtf8().constData();
    std::string port = portText->displayText().toUtf8().constData();
    this->player_name = pnameText->displayText().toUtf8().constData();
    std::cout << "El usuario intenta conectarse a " << ip << ":" << port << std::endl;

    try {
        SocketConnection skt(ip, port);
        this->protocol = new Protocol(std::move(skt));
        std::cout << "Socket creado para conexión con servidor " << skt.sockfd << std::endl;
    } catch (const SocketError & e) {
        std::cout << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error de conexión.");
        msgBox.setText("No se pudo conectar con el servidor. Por favor, chequee ip y puerto.");
        msgBox.exec();
        return;
    }
    std::cout << "Conexion con servidor establecida" << std::endl;

    goLobby();
}

void ClientLobby::goLobby(void) {
    this->protocol->sendName(this->player_name);
    // Recibe el nuevo nombre (si hubo colisión) que le asigna el servidor.
    this->protocol->getPlayerName(this->player_name);
    std::cout << "El servidor me bautizó como: " << this->player_name << std::endl;
    QLabel* playerName = findChild<QLabel*>("playerName");
    playerName->setText(this->player_name.c_str());

    this->pages->setCurrentIndex(PAGE_LOBBY_INDEX);

    feedLobby();
}

void ClientLobby::createMatch(void) {
    this->pages->setCurrentIndex(PAGE_MATCH_CREATE);
}

void ClientLobby::exitLobby(void) {
    std::cout << "Me voy del lobby" << std::endl;
    this->pages->setCurrentIndex(PAGE_CONNECTION_INDEX);
    Event new_event(a_quitLobby, 1);
    this->protocol->sendEvent(new_event);
    delete this->protocol;
}

void ClientLobby::joinMatch(void) {
    std::cout << "Me uno a una partida!" << std::endl;
}

void ClientLobby::refreshLobby(void) {
    std::cout << "Refresh del lobby" << std::endl;
    cleanLobby();
    Event new_event(a_refreshLobby, 1);
    this->protocol->sendEvent(new_event);
    feedLobby();
}

void ClientLobby::waitForPlayersOnCreatedMatch(void) {
    QLineEdit * matchName = findChild<QLineEdit*>("text_game_name");

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

    std::cout << "Lanzo una partida en espera!" << std::endl;
    this->pages->setCurrentIndex(PAGE_WAITING_MATCH_INDEX);
    Event new_event(a_createMatch);
    this->protocol->sendEvent(new_event);
}

void ClientLobby::backLobby(void) {
    this->pages->setCurrentIndex(PAGE_LOBBY_INDEX);
    refreshLobby();
}

void ClientLobby::cleanLobby(void) {
    QList<QListWidgetItem*>::iterator it;
    for (it = this->lobby_games.begin(); it != this->lobby_games.end();) {
        delete (*it);
        it = this->lobby_games.erase(it);
    }
}

void ClientLobby::feedLobby(void) {
    std::cout << "Alimentando lobby!" << std::endl;
    QListWidget * matchsList = findChild<QListWidget*>("list_matchs");
    YAML::Node gameStatus;
    this->protocol->rcvGameStatus(gameStatus);

    std::stringstream ss;
    ss << gameStatus;
    std::cout << ss.str() << std::endl;

    YAML::Node::const_iterator it;
    for (it = gameStatus["games"].begin(); it != gameStatus["games"].end(); it++) {
        std::string text_row;
        text_row = (*it)["name"].as<std::string>();
        text_row += " - Created By: ";
        text_row += (*it)["creator"].as<std::string>();
        text_row += " - With: ";
        text_row += (*it)["players"].as<std::string>();
        text_row += "/3 players.";
        this->lobby_games.append(new QListWidgetItem());
        this->lobby_games.last()->setText(tr(text_row.c_str()));
        matchsList->insertItem(1, this->lobby_games.last());
    }
}

void ClientLobby::chooseMap(void) {
    QString map_path;
    map_path = QFileDialog::getOpenFileName(this, tr("Choose a map"), "/home", tr("Tar gzipped (*.tar.gz)"));
    if (map_path.length() > 0) {
        this->map_game_path = map_path.toUtf8().constData();
        std::cout << "El mapa elegido es " << this->map_game_path << std::endl;
        QLabel* currentMapPath = findChild<QLabel*>("text_current_map_path");
        currentMapPath->setText(this->map_game_path.c_str());
    } else {
        std::cout << "No se eligio un mapa." << std::endl;
    }
}

void ClientLobby::feedWaitingPlayers(void) {
    std::cout << "Alimento la lista de jugadores en espera." << std::endl;
}

void ClientLobby::startWaitingMatch(void) {
    std::cout << "Comienzo juego" << std::endl;
}

void ClientLobby::cancelWaitingMatch(void) {
    std::cout << "Cancelo juego en espera." << std::endl;
}