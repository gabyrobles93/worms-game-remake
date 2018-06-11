#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "client.h"
#include "protocol.h"
#include "event.h"
#include "yaml.h"

Client::Client(Protocol prt, std::string & pn) :
protocol(std::move(prt)){
    this->player_name = pn;
    this->status = lobby;
    this->in_match_id = 0;
}

void Client::sendGamesStatus(YAML::Node gameStatusNode) {
/*     std::cout << "Soy la conexion con el cliente y voy a enviar el games.yml" << std::endl;
    std::stringstream ss;
    ss << gameStatusNode;
    std::cout << ss.str() << std::endl; */
    protocol.sendGameStatus(gameStatusNode);
}

Event Client::rcvEvent(void) {
    return this->protocol.rcvEvent();
}

std::string Client::getPlayerName(void) {
    return this->player_name;
}

void Client::setStatus(client_status_t new_status) {
    this->status = new_status;
}

client_status_t Client::getStatus(void) {
    return this->status;
}

void Client::sendResponse(int code, std::string & msg) {
    YAML::Node response;
    response["code"] = code;
    response["msg"] = msg;
    this->protocol.sendMsg(response);
}

void Client::setJoinedMatchGameCreator(std::string & jmn) {
    this->joined_match_creator_name = jmn;
}

void Client::clearJoinedMatchGameCreator(void) {
    this->joined_match_creator_name.clear();
}

std::string Client::getJoinedMatchCreatorName(void) {
    return this->joined_match_creator_name;
}

void Client::sendWaitingPlayers(std::vector<std::string> players) {
    YAML::Node response;
    response["waiting_players"];
    response["waiting_players"] = players;
    this->protocol.sendMsg(response);
}

void Client::sendGameStart(int code, std::string & msg, std::string & team_id) {
    YAML::Node response;
    response["code"] = code;
    response["msg"] = msg;
    response["team_id"] = team_id;
    this->protocol.sendMsg(response);
}

void Client::sendGameMap(YAML::Node mapNode) {
    this->protocol.sendGameMap(mapNode);
}

void Client::sendSnapShot(std::stringstream & ss) {
    this->protocol.sendGameMapAsString(ss);
}

void Client::setIdInMatch(size_t id) {
    this->in_match_id = id;
}

size_t Client::getIdInMatch(void) {
    return this->in_match_id;
}