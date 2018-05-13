#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include "yaml-cpp/yaml.h"
#include "thread.h"
#include "protocol.h"
#include "client_lobby_feeder.h"
#include "socket_error.h"
#include "protocol_error.h"

ClientLobbyFeeder::ClientLobbyFeeder(Protocol & prot) :
protocol(prot)
{
    std::cout << "Lobby feeder creado" << std::endl;
    this->running = true;
}

ClientLobbyFeeder::~ClientLobbyFeeder(void) {
    std::cout << "Destruyendo lobby feeder." << std::endl;
}

void ClientLobbyFeeder::run(void) {
    while(1) {
         try {
            this->games_status.open("games.yml", std::ios::out|std::ios::binary|std::ios::trunc);
            std::cout << "Esperando archivo de game status." << std::endl;
            this->protocol.rcvFile(this->games_status);
            std::cout << "Recibido archivo de estados de juego." << std::endl;
            this->games_status.close();
            feedGamesTable();
        } catch(const ProtocolError & e) {
            std::cout << "Fin del ciclo de lobby feeder. " << std::endl;
            break;
        }       
    }

    this->running = false;
}

void ClientLobbyFeeder::stop(void) {
    std::cout << "Haciendo shutdown de socket lobby feeder." << std::endl;
    this->protocol.sendExitLobby();
}

void ClientLobbyFeeder::feedGamesTable(void) {
    std::cout << "Actualizo tabla de lobby." << std::endl;

    YAML::Node games_file = YAML::LoadFile("games.yml");
    const YAML::Node& games = games_file["games"];
    for (YAML::const_iterator it = games.begin(); it != games.end(); ++it) {
        const YAML::Node& game = *it;
        std::cout << "Nombre del juego: " << game["name"].as<std::string>() << std::endl;;
        std::cout << "Creador: " << game["creator"].as<std::string>() << std::endl; 
        std::cout << "Jugadores: " << game["players"].as<size_t>() << "/3" << std::endl;

        std::string game_name = game["name"].as<std::string>();
        std::string game_creator = game["creator"].as<std::string>();
        std::string game_players = game["players"].as<std::string>();
        game_players += "/3";

        this->games_table->insertRow(this->games_table->rowCount());

        QTableWidgetItem *table_game_name = new QTableWidgetItem(game_name.c_str());
        table_game_name->setFlags(table_game_name->flags() ^ Qt::ItemIsEditable);
        this->games_table->setItem(this->games_table->rowCount()-1, 0, table_game_name);

        QTableWidgetItem *table_game_creator = new QTableWidgetItem(game_creator.c_str());
        table_game_creator->setFlags(table_game_creator->flags() ^ Qt::ItemIsEditable);
        this->games_table->setItem(this->games_table->rowCount()-1, 1, table_game_creator);
        
        QTableWidgetItem *table_game_players = new QTableWidgetItem(game_players.c_str());
        table_game_players->setFlags(table_game_players->flags() ^ Qt::ItemIsEditable);
        this->games_table->setItem(this->games_table->rowCount()-1, 2, table_game_players);
    }

    std::cout << "Tabla de lobby actualizada" << std::endl;
}

bool ClientLobbyFeeder::isRunning(void) const {
    return this->running;
}

size_t ClientLobbyFeeder::getId(void) const {
    return 0;
}

void ClientLobbyFeeder::setGamesTable(QTableWidget* table) {
    this->games_table = table;
}