#include "client_handler.h"
#include "types.h"

ClientHandler::ClientHandler(SocketReadWrite skt, World & w) :
protocol(std::move(skt)),
world(w) {
    this->keep_running = true;
}

bool ClientHandler::isRunning(void) const {
    return true;
}

size_t ClientHandler::getId(void) const {
    return 0;
}

void ClientHandler::run(void) {
/*     while (keep_running) {
        action_t event;
        this->protocol.rcvEvent(event);
        if (1 gameStatus.isMyTurn(this->team_id) ) {
            switch (event) {
                case a_moveLeft: {
                    this->world.moveLeft(1);
                    break;
                }
                case a_moveRight: {
                    this->world.moveRight(1);
                    break;
                }
                default: break;
            }
        }
    } */
}

ClientHandler::~ClientHandler(void) {

}