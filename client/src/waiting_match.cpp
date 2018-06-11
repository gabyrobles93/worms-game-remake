#include "waiting_match.h"
#include "thread.h"
#include "protocol.h"
#include "yaml.h"
#include <qt5/QtWidgets/QMessageBox>
#include <fstream>
#include "client_game.h"

WaitingMatch::WaitingMatch(Protocol * p) :
protocol(p) {
    this->keep_running = true;
}

bool WaitingMatch::isRunning(void) const {
    return this->keep_running;
}

void WaitingMatch::run(void) {
    while (keep_running) {
        YAML::Node msg;
        this->protocol->rcvMsg(msg);

        std::cout << "Mensaje del servidor recibido en una waiting match:" << std::endl;
        std::stringstream ss;
        ss << msg;
        std::cout << ss.str() << std::endl;

        if (msg["code"].as<int>() == 1) {
            if (msg["msg"].as<std::string>() == "exited") {
                std::cout << "El hoster te dio el ok para que salgas de la partida.." << std::endl;
                this->keep_running = false;
                return;
            }
            if (msg["msg"].as<std::string>() == "started") {
                std::cout << "El hoster decidio que la partida empieza ahora!" << std::endl;
                size_t team_id = msg["team_id"].as<size_t>();
                std::cout << "El hoster me asignó el id team: " << team_id << std::endl;
                // Este evento se manda para destrabar el event receiver del servidor y que pueda pasarle el socket
                // al handler de la partida...
                Event new_event(a_goToMatch);
                this->protocol->sendEvent(new_event);
                // Recibo el mapa del juego
                std::string file_map_path = "map.tar.gz";
                std::fstream map_file(file_map_path, std::fstream::in | std::fstream::binary | std::fstream::trunc);
                this->protocol->rcvFile(map_file);
                map_file.close();           
                std::cout << "Aca instancio un juego cliente y lo lanzo pasandole el protocolo." << std::endl;
                ClientGame the_game(file_map_path, this->protocol, team_id);
                the_game.startGame();
            }
        } else if (msg["code"].as<int>() == 0) {
            if (msg["msg"].as<std::string>() == "aborted") {
                std::cout << "El hoster decidió cancelar la partida en espera." << std::endl;
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