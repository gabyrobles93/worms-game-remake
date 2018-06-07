#ifndef __WAITING_GAME_H__
#define __WAITING_GAME_H__

#include <string>

class WaitingGame {
    private:
        std::string creator;
    public:
        WaitingGame(std::string &);
        std::string const & getCreator(void);
};

#endif