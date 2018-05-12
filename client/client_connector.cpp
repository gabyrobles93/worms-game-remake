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
    skt = NULL;
    connectEvents();
}

client_connector::~client_connector()
{
    delete ui;
    if (skt != NULL)
        delete skt;
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
    QPlainTextEdit* ipText = findChild<QPlainTextEdit*>("ipTextInput");
    QPlainTextEdit* portText = findChild<QPlainTextEdit*>("portTextInput");
    std::string ip = ipText->toPlainText().toUtf8().constData();
    std::string port = portText->toPlainText().toUtf8().constData();
    std::cout << "El usuario intenta conectarse a " << ip << ":" << port << std::endl;

    try {
        this->skt = new SocketConnection(ip, port);
    } catch (const SocketError & e) {
        std::cout << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Can't connect");
        msgBox.setText("Can't connect with server. Check ip/host and port/service.");
        msgBox.exec();
        return;
    }

    std::cout << "Conexion con servidor establecida" << std::endl;

    lobby.skt = this->skt;
    lobby.show();
    this->hide();
}
