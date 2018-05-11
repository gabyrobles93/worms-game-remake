#include "client_connector.h"
#include "ui_client_connector.h"

client_connector::client_connector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client_connector)
{
    ui->setupUi(this);
    connectEvents();
}

client_connector::~client_connector()
{
    delete ui;
}

void client_connector::connectEvents(void)
{
    // Conecto el evento del boton exit
    QPushButton* exitButton = findChild<QPushButton*>("exitButton");
    QObject::connect(exitButton, &QPushButton::clicked,
                     this, &client_connector::close);
}
