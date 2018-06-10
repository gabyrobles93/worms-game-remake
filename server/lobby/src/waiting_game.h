#ifndef __WAITING_GAME_H__
#define __WAITING_GAME_H__

#include <string>
#include <vector>
#include "client.h"

class WaitingGame {
    private:
        std::vector<Client*> members;
        std::string match_name;
        size_t players_qty;
        size_t joined_players;

    public:
        WaitingGame(Client *, std::string &, size_t);
        std::string getCreatorName(void);
        std::string getMatchName(void);
        size_t getPlayersQty(void);
        size_t getJoinedPlayersQty(void);
        bool hasFreeSlots(void);
        void addPlayer(Client *);
        void rmPlayer(std::string &);
        std::vector<std::string> getWaitingPlayersName(void);
        void notifyAllStartGame(void);
        void notifyAllCancellGame(void);
};

#endif