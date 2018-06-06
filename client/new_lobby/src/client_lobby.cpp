#include <iostream>
#include <sstream>
#include <qt5/QtWidgets/QMessageBox>
#include "QStackedWidget"
#include "client_lobby.h"
#include "ui_clientlobby.h"
#include "socket.h"
#include "socket_error.h"

#define CONNECTION_PAGE_INDEX 0
#define LOBBY_PAGE_INDEX 1

ClientLobby::ClientLobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientLobby)
{
    ui->setupUi(this);
    connectEvents();
}

ClientLobby::~ClientLobby()
{
    QList<QListWidgetItem*>::iterator it;
    for (it = this->lobby_games.begin(); it != this->lobby_games.end(); it++) {
        delete (*it);
    }
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

    QStackedWidget * pages = findChild<QStackedWidget*>("pages_client");
    pages->setCurrentIndex(LOBBY_PAGE_INDEX);

    feedLobby();
}

void ClientLobby::createMatch(void) {
    std::cout << "Creo una partida!" << std::endl;
}

void ClientLobby::exitLobby(void) {
    std::cout << "Me voy del lobby" << std::endl;
    QStackedWidget * pages = findChild<QStackedWidget*>("pages_client");
    pages->setCurrentIndex(CONNECTION_PAGE_INDEX);
    delete this->protocol;
}

void ClientLobby::joinMatch(void) {
    std::cout << "Me uno a una partida!" << std::endl;
}

void ClientLobby::refreshLobby(void) {
    std::cout << "Refresh del lobby" << std::endl;
}

void ClientLobby::feedLobby(void) {
    std::cout << "Alimentando lobby!" << std::endl;
    QListWidget * matchsList = findChild<QListWidget*>("list_matchs");
    YAML::Node gameStatus;
    this->protocol->rcvGameStatus(gameStatus);
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