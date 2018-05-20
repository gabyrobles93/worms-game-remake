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
        this->protocol.sendEvent(action);
    }
}

void EventSender::stop(void) {
    this->keep_runing = false;
}