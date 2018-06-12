#include <fstream>
#include "lobby_attendant.h"
#include "thread.h"
#include "client.h"
#include "yaml.h"

LobbyAttendant::LobbyAttendant(Client * c, ProtectedWaitingGames & wg) :
client(c),
waiting_games (wg) {
    this->keep_running = true;
    this->player_name = client->getPlayerName();
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
        if (new_event.goToMatch()) {
            std::cout << "Hay que esperar aca hasta que termine la partida." << std::endl;
            std::string creator_match_name = this->client->getJoinedMatchCreatorName();
            this->waiting_games.waitGameUntilFinish(creator_match_name);
            std::cout << "La partida termino asique dejo de esperar." << std::endl;
            continue;
        }
        processEvent(new_event);
    }
}

void LobbyAttendant::processEvent(Event & event) {
    YAML::Node event_node = event.getNode();
    std::cout << "Evento recibido del cliente " << this->player_name << std::endl;

    action_t action = (action_t) event_node["event"]["action"].as<int>();

    switch(action) {
        case a_refreshLobby: {
            refreshLobby();
            break;
        }
        case a_createMatch: {
            std::string match_name = event_node["event"]["match_name"].as<std::string>();
            size_t players_qty = event_node["event"]["map_players_qty"].as<size_t>();
            createMatch(match_name, players_qty);
            break;
        }
        case a_rmWaitingMatch: {
            removeWaitingMatch();
            break;
        }
        case a_joinWaitingMatch: {
            std::cout << "uniendome a partida" << std::endl;
            std::string match_creator_name = event_node["event"]["creator_name"].as<std::string>();
            joinWaitingMatch(match_creator_name);
            break;
        }
        case a_exitWaitingMatch: {
            exitWaitingMatch();
            break;
        }
        case a_refreshWaitingList: {
            refreshWaitingList();
            break;
        }
        case a_startMatch: {
            startMatch();
            break;
        }
        default: break;
    }
}

void LobbyAttendant::refreshLobby(void) {
    this->client->sendGamesStatus(this->waiting_games.getGamesInfoNode());
}

void LobbyAttendant::createMatch(std::string & match_name, size_t map_players_qty) {
    std::cout << "El cliente " << this->player_name << " ha creado una partida." << std::endl;
    this->client->setStatus(creator);
    WaitingGame * new_waiting_game = new WaitingGame(this->client, match_name, map_players_qty);
    this->waiting_games.addNewWaitingGame(this->player_name, new_waiting_game);
    this->client->setJoinedMatchGameCreator(match_name);
}

void LobbyAttendant::removeWaitingMatch(void) {
    std::cout << "El creador de la partida en espera " << this->waiting_games.getGameName(this->player_name) << " ha cancelado la partida." << std::endl;
    this->client->setStatus(lobby);
    this->client->clearJoinedMatchGameCreator();
    this->waiting_games.notifyAllCancellGame(this->player_name);
    this->waiting_games.removeGame(this->player_name);
}

void LobbyAttendant::joinWaitingMatch(std::string & match_creator_name) {
    std::cout << "El cliente " << this->player_name << " intenta joinearse a la partida de " << match_creator_name << std::endl;
    if (this->waiting_games.gameHasFreeSlots(match_creator_name)) {
        this->waiting_games.addPlayerToGame(match_creator_name, this->client);
        this->client->setStatus(joined);
        std::string msg = "";
        this->client->sendResponse(1, msg);
        this->client->setJoinedMatchGameCreator(match_creator_name);
    } else {
        std::string msg = "La partida está llena.";
        this->client->sendResponse(0, msg);
    }    
}

void LobbyAttendant::exitWaitingMatch(void) {
    std::cout << "saliendo de partida en espera a la que me uni." << std::endl;
    std::string joined_match_creator_name = this->client->getJoinedMatchCreatorName();
    this->waiting_games.rmvPlayerFromGame(joined_match_creator_name, this->player_name);
    this->client->clearJoinedMatchGameCreator();
    std::string msg = "exited";
    this->client->sendResponse(1, msg);
}

void LobbyAttendant::refreshWaitingList(void) {
    std::cout << "El creador de partida " << this->player_name << " quiere hacer refresh de la lista de jugadores en espera." << std::endl;
    this->client->sendWaitingPlayers(this->waiting_games.getWaitingPlayers(this->player_name));
}

void LobbyAttendant::startMatch(void) {
    std::cout << "El jugador " << this->player_name << " intenta iniciar su partida." << std::endl;
    if (this->waiting_games.gameHasFreeSlots(this->player_name)) {
        // No se puede iniciar la partida, pues faltan lugares que ocupar.
        std::string msg = "La partida no tiene los suficientes jugadores para iniciar.";
        this->client->sendResponse(0, msg);
    } else {
        // La partida puede comenzar
        std::cout << "La partida puede comenzar, se le informará a todos los participantes." << std::endl;
        this->waiting_games.notifyAllStartGame(this->player_name);
        std::string map_path = this->player_name + "-map-tar-gz";
        std::fstream map_file(map_path, std::fstream::out | std::fstream::binary | std::fstream::trunc);
        this->client->rcvMapGame(map_file);
        std::cout << "Recibido el mapa del cliente creador. Va a iniciarse la partida." << std::endl;
        map_file.close();
        this->waiting_games.startWaitingGame(this->player_name, map_path);
        this->waiting_games.removeGame(this->player_name);
        std::cout << "Waiting game removido." << std::endl;
    }
}