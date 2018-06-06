#include "client_lobby.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientLobby w;
    w.show();

    return a.exec();
}
