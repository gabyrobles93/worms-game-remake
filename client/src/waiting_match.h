#ifndef __WAITING_MATCH_H__
#define __WAITING_MATCH_H__

#include "thread.h"
#include "protocol.h"

class WaitingMatch : public Thread {
    private:
        Protocol * protocol;
        bool keep_running;

        size_t getId(void) const;

    public:
        WaitingMatch(Protocol *);
        bool isRunning(void) const;
        virtual void run(void);
        void stop(void);
};

#endif