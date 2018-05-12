#include <iostream>
#include <QMainWindow>
#include "client_lobby.h"
#include "ui_client_lobby.h"
#include "client_connector.h"
#include "protocol.h"

client_lobby::client_lobby(QWidget *parent, SocketReadWrite skt, std::string & pname) :
    QWidget(parent),
    ui(new Ui::client_lobby),
    protocol(std::move(skt)),
    player_name(pname)
{
    ui->setupUi(this);
    QTableWidget* gamesTable = findChild<QTableWidget*>("gamesTable");
    QLabel* playerName = findChild<QLabel*>("playerName");
    gamesTable->setColumnWidth(0, 275);
    gamesTable->setColumnWidth(1, 110);
    gamesTable->setColumnWidth(2, 62);
    playerName->setText(QString::fromStdString(this->player_name));
    connectEvents();
    introduceToServer();
}

client_lobby::~client_lobby(void)
{
    std::cout << "Destruyendo widget de Lobby." << std::endl;
    delete ui;
}

void client_lobby::connectEvents(void) {
    // Conecto el evento del boton exit
    
    QPushButton* exitLobbyButton = findChild<QPushButton*>("exitLobbyButton");
    QObject::connect(exitLobbyButton, &QPushButton::clicked,
                    this, &client_lobby::close);

    // Conecto el evento del boton join
    QPushButton* joinGameButton = findChild<QPushButton*>("joinGameButton");
    QObject::connect(joinGameButton, &QPushButton::clicked,
                     this, &client_lobby::close);
                    
    // Conecto el evento del boton create
    QPushButton* createGameButton = findChild<QPushButton*>("createGameButton");
    QObject::connect(createGameButton, &QPushButton::clicked,
                     this, &client_lobby::close);
}

void client_lobby::introduceToServer(void) {
    this->protocol.sendName(this->player_name);
    // Recibe el nuevo nombre (si hubo colisión) que le asigna el servidor.
    this->protocol.getPlayerName(this->player_name);

    std::cout << "El servidor me bautizó como: " << this->player_name << std::endl;
}