#ifndef __WAITING_GAME_H__
#define __WAITING_GAME_H__

#include <string>
#include <vector>

class WaitingGame {
    private:
        std::string creator;
        std::vector<std::string> members;
        std::string match_name;
        size_t players_qty;
        size_t joined_players;

    public:
        WaitingGame(std::string &, std::string &, size_t);
        std::string const & getCreator(void);
        std::string const & getMatchName(void);
        size_t getPlayersQty(void);
        bool hasFreeSlots(void);
        void addPlayer(std::string &);
};

#endif