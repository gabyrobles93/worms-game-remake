#include <iostream>
#include <string>
#include <sstream>
#include "socket.h"
#include "event_sender.h"
#include "blocking_queue.h"
#include "thread.h"
#include "protocol.h"
#include "types.h"
#include "event.h"

EventSender::EventSender(Protocol * p, Queue<Event> & e) :
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
    while (keep_runing) {
        Event event = this->events.pop();
        YAML::Node evento = event.getNode();
        if (!event.quit()) {
            this->protocol->sendEvent(event);
        } else {
            std::cout << "Enviando evento de quit." << std::endl;
            this->protocol->sendEvent(event);
            return;
        }
    }
}

void EventSender::stop(void) {
    this->keep_runing = false;
}