#ifndef __WAITING_GAME_H__
#define __WAITING_GAME_H__

#include <string>

class WaitingGame {
    private:
        std::string creator;
        std::string match_name;
    public:
        WaitingGame(std::string &, std::string &);
        std::string const & getCreator(void);
        std::string const & getMatchName(void);
};

#endif