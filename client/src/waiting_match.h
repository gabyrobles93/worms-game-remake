#ifndef __WAITING_MATCH_H__
#define __WAITING_MATCH_H__

#include "thread.h"
#include "protocol.h"
#include "QStackedWidget"

class WaitingMatch : public Thread {
    private:
        Protocol * protocol;
        QStackedWidget * pages;
        bool keep_running;

        size_t getId(void) const;

    public:
        WaitingMatch(Protocol *, QStackedWidget*);
        bool isRunning(void) const;
        virtual void run(void);
        void stop(void);
};

#endif