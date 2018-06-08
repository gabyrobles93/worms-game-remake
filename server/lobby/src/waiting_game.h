#ifndef __WAITING_GAME_H__
#define __WAITING_GAME_H__

#include <string>

class WaitingGame {
    private:
        std::string creator;
        std::string match_name;
        size_t players_qty;

    public:
        WaitingGame(std::string &, std::string &, size_t);
        std::string const & getCreator(void);
        std::string const & getMatchName(void);
        size_t getPlayersQty(void);
};

#endif