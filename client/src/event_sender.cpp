#include <iostream>
#include <string>
#include "socket.h"
#include "event_sender.h"
#include "blocking_queue.h"
#include "thread.h"
#include "protocol.h"
#include "types.h"

EventSender::EventSender(Protocol & p, BlockingQueue<action_t> & e) :
protocol(p),
events(e) {
    keep_runing = true;
}

EventSender::~EventSender(void) {
    this->protocol.sendExit();
}

bool EventSender::isRunning(void) const {
    return true;
}

size_t EventSender::getId(void) const {
    return 0;
}

void EventSender::run(void) {
    action_t action;
    while (keep_runing) {
        action = this->events.pop();
        if (action != a_quitGame)
            this->protocol.sendEvent(action);
        else {
            this->protocol.sendEvent(a_quitGame);
            return;
        }
    }
}

void EventSender::stop(void) {
    this->keep_runing = false;
}