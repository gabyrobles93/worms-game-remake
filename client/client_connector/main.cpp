#include "client_connector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client_connector w;
    w.show();

    return a.exec();
}
