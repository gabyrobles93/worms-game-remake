#include <iostream>
#include <QMessageBox>
#include "client_connector.h"
#include "ui_client_connector.h"
#include "socket.h"
#include "socket_error.h"
#include "client_lobby.h"

client_connector::client_connector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client_connector)
{
    ui->setupUi(this);
    this->lobby = NULL;
    connectEvents();
}

client_connector::~client_connector()
{
    std::cout << "Destruyendo widget de Client Connector." << std::endl;
    delete ui;
    if (this->lobby != NULL)
        delete this->lobby;
}

void client_connector::connectEvents(void)
{
    // Conecto el evento del boton exit
    QPushButton* exitButton = findChild<QPushButton*>("exitButton");
    QObject::connect(exitButton, &QPushButton::clicked,
                     this, &client_connector::close);

    // Conecto el evento del boton exit
    QPushButton* connectButton = findChild<QPushButton*>("connectButton");
    QObject::connect(connectButton, &QPushButton::clicked,
                     this, &client_connector::connectToServer);
}

void client_connector::connectToServer(void)
{
    QLineEdit* ipText = findChild<QLineEdit*>("ipTextInput");
    QLineEdit* portText = findChild<QLineEdit*>("portTextInput");
    QLineEdit* pnameTex = findChild<QLineEdit*>("playerNameInput");
    std::string ip = ipText->displayText().toUtf8().constData();
    std::string port = portText->displayText().toUtf8().constData();
    std::string player_name = pnameTex->displayText().toUtf8().constData();
    std::cout << "El usuario intenta conectarse a " << ip << ":" << port << std::endl;

    try {
        SocketConnection skt(ip, port);
        std::cout << "Socket creado para conexión con servidor " << skt.sockfd << std::endl;
        this->lobby = new client_lobby(0, std::move(skt), player_name);
    } catch (const SocketError & e) {
        std::cout << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Can't connect");
        msgBox.setText("Can't connect with server. Check ip/host and port/service.");
        msgBox.exec();
        return;
    }

    std::cout << "Conexion con servidor establecida" << std::endl;

    switchToLobby();
}

void client_connector::switchToLobby(void) {
    this->lobby->show();
    this->hide();
}
