#include "client_lobby.h"
#include "ui_client_lobby.h"

client_lobby::client_lobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client_lobby)
{
    ui->setupUi(this);
    QTableWidget* gamesTable = findChild<QTableWidget*>("gamesTable");
    gamesTable->setColumnWidth(0, 275);
    gamesTable->setColumnWidth(1, 110);
    gamesTable->setColumnWidth(2, 62);
}

client_lobby::~client_lobby()
{
    delete ui;
}
