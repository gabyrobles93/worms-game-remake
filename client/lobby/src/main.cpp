#include <iostream>
#include "client_connector.h"
#include "socket_error.h"
#include <QApplication>

int main(int argc, char *argv[])
try {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://images/applogo2.png"));
    client_connector w;
    w.show();

    return a.exec();
} catch(const SocketError & e) {
    std::cout << e.what() << std::endl;
}
