#ifndef __PROTECTED_WAITING_GAMES_H__
#define __PROTECTED_WAITING_GAMES_H__

#include <mutex>
#include <map>
#include <string>
#include <vector>
#include <string>
#include "waiting_game.h"
#include "yaml.h"

class ProtectedWaitingGames {
    private:
        std::mutex mutex;
        std::map<std::string, WaitingGame*> waiting_games;
    public:
        ProtectedWaitingGames(void);
        void addNewWaitingGame(std::string &, WaitingGame *);
        YAML::Node getGamesInfoNode(void);
        std::string getGameName(std::string &);
        void removeGame(std::string &);
        bool gameHasFreeSlots(std::string &);
        void addPlayerToGame(std::string &, Client *);
        void rmvPlayerFromGame(std::string &, std::string &);
        std::vector<std::string> getWaitingPlayers(std::string &);
        void notifyAllStartGame(std::string &);
        void notifyAllCancellGame(std::string &);
        void startWaitingGame(std::string &, std::string &);
        void waitGameUntilFinish(std::string &);
};

#endif