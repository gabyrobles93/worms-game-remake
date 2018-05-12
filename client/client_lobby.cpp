#include <iostream>
#include <QMainWindow>
#include "client_lobby.h"
#include "ui_client_lobby.h"
#include "client_connector.h"
#include "protocol.h"

client_lobby::client_lobby(QWidget *parent, SocketReadWrite skt) :
    QWidget(parent),
    ui(new Ui::client_lobby),
    protocol(std::move(skt))
{
    ui->setupUi(this);
    QTableWidget* gamesTable = findChild<QTableWidget*>("gamesTable");
    gamesTable->setColumnWidth(0, 275);
    gamesTable->setColumnWidth(1, 110);
    gamesTable->setColumnWidth(2, 62);

     connectEvents();
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
