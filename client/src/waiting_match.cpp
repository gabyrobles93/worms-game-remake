#include "waiting_match.h"
#include "thread.h"
#include "protocol.h"
#include "yaml.h"
#include <qt5/QtWidgets/QMessageBox>
#include "QStackedWidget"
#include <fstream>
#include "client_game.h"

#define PAGE_LOBBY_INDEX 1

WaitingMatch::WaitingMatch(Protocol * p, QStackedWidget * pag) :
protocol(p),
pages(pag) {
    this->keep_running = true;
}

bool WaitingMatch::isRunning(void) const {
    return this->keep_running;
}

void WaitingMatch::run(void) {
    while (keep_running) {
        YAML::Node msg;
        this->protocol->rcvMsg(msg);

        if (msg["code"].as<int>() == 1) {
            if (msg["msg"].as<std::string>() == "exited") {
                this->keep_running = false;
                return;
            }
            if (msg["msg"].as<std::string>() == "started") {
                size_t team_id = msg["team_id"].as<size_t>();
                // Este evento se manda para destrabar el event receiver del servidor y que pueda pasarle el socket
                // al handler de la partida...
                Event new_event(a_goToMatch);
                this->protocol->sendEvent(new_event);      
                ClientGame the_game(this->protocol, team_id);
                the_game.startGame();
                this->pages->setCurrentIndex(PAGE_LOBBY_INDEX);
                this->keep_running = false;
                return;
            }
        } else if (msg["code"].as<int>() == 0) {
            if (msg["msg"].as<std::string>() == "aborted") {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Partida cancelada.");
                msgBox.setText("El creador del juego canceló la partida.");
                msgBox.exec();
                this->keep_running = false;
                return;
            }
        }
    }
}

void WaitingMatch::stop(void) {
    this->keep_running = false;
}

size_t WaitingMatch::getId(void) const {
    return 0;
}