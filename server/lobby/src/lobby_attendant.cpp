#include "lobby_attendant.h"
#include "thread.h"
#include "client.h"
#include "yaml.h"

LobbyAttendant::LobbyAttendant(Client * c, ProtectedWaitingGames & wg) :
client(c),
waiting_games (wg) {
    this->keep_running = true;
}

bool LobbyAttendant::isRunning(void) const {
    return this->keep_running;
}

size_t LobbyAttendant::getId(void) const {
    return 0;
}

void LobbyAttendant::stop(void) {
    this->keep_running = false;
}

void LobbyAttendant::run(void) {
    while (this->keep_running) {
        Event new_event = this->client->rcvEvent();
        if (new_event.quit()) {
            std::cout << "El cliente " << this->client->getPlayerName() << " ha saldo del lobby." << std::endl;
            this->client->setStatus(quited);
            this->keep_running = false;
            return;
        }
        processEvent(new_event);
    }
}

void LobbyAttendant::processEvent(Event & event) {
    YAML::Node event_node = event.getNode();
    std::cout << "Evento recibido del cliente " << this->client->getPlayerName() << std::endl;
    std::cout << "El nodo del evento es: " << std::endl;
    std::stringstream ss;
    ss << event_node;
    std::cout << ss.str() << std::endl;

    action_t action = (action_t) event_node["event"]["action"].as<int>();
    std::string player_name =  this->client->getPlayerName();

    switch(action) {
        case a_refreshLobby: {
            this->client->sendGamesStatus(this->waiting_games.getGamesInfoNode());
            break;
        }
        case a_createMatch: {
            std::cout << "INTENCIONES DE CREAR PARTIDA EN ESPERA." << std::endl;
            std::string match_name = event_node["event"]["match_name"].as<std::string>();
            size_t map_players_qty = event_node["event"]["map_players_qty"].as<size_t>();
            std::cout << "El cliente " << player_name << " ha creado una partida." << std::endl;
            this->client->setStatus(creator);
            WaitingGame * new_waiting_game = new WaitingGame(player_name, match_name, map_players_qty);
            this->waiting_games.addNewWaitingGame(player_name, new_waiting_game);
            this->client->setJoinedMatchGameCreator(match_name);
            break;
        }
        case a_rmWaitingMatch: {
            std::cout << "El creador de la partida en espera " << this->waiting_games.getGameName(player_name) << " ha cancelado la partida." << std::endl;
            this->waiting_games.removeGame(player_name);
            this->client->setStatus(lobby);
            this->client->clearJoinedMatchGameCreator();
            // INFORMARLE A TODOS QUE BYE...
            break;
        }
        case a_joinWaitingMatch: {
            std::cout << "uniendome a partida" << std::endl;
            std::string match_creator_name = event_node["event"]["creator_name"].as<std::string>();
            std::cout << "El cliente " << player_name << " intenta joinearse a la partida de " << match_creator_name << std::endl;
            if (this->waiting_games.gameHasFreeSlots(match_creator_name)) {
                this->waiting_games.addPlayerToGame(match_creator_name, player_name);
                this->client->setStatus(joined);
                std::string msg = "";
                this->client->sendResponse(1, msg);
                this->client->setJoinedMatchGameCreator(match_creator_name);
            } else {
                std::string msg = "La partida está llena.";
                this->client->sendResponse(0, msg);
            }    
            break;
        }
        case a_exitWaitingMatch: {
            std::cout << "saliendo de partida en espera a la que me uni" << std::endl;
            std::string joined_match_creator_name = this->client->getJoinedMatchCreatorName();
            this->waiting_games.rmvPlayerFromGame(joined_match_creator_name, player_name);
            break;
        }
        case a_refreshWaitingList: {
            std::cout << "El creador de partida " << player_name << " quiere hacer refresh de la lista de jugadores en espera." << std::endl;
            this->client->sendWaitingPlayers(this->waiting_games.getWaitingPlayers(player_name));
            break;
        }
        default: break;
    }
}