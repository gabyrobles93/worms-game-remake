#include "client_lobby.h"
#include "socket_error.h"
#include "paths.h"
#include "client_settings.h"
#include <QApplication>

#define MAX_QUEUE_MODELS 256

// Variable global
Paths gPath;
ClientSettings gClientSettings;

int main(int argc, char *argv[]) try {
    QApplication a(argc, argv);
    ClientLobby w;
    w.show();

    return a.exec();
} catch(const SocketError & e) {
	std::cout << e.what() << std::endl;
} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
}
