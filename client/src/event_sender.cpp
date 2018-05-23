#include <iostream>
#include <string>
#include "socket.h"
#include "event_sender.h"
#include "blocking_queue.h"
#include "thread.h"
#include "protocol.h"
#include "types.h"
#include "event.h"

EventSender::EventSender(Protocol & p, Queue<Event> & e) :
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
    while (keep_runing) {
        Event event = this->events.pop();
        if (!event.quit()) {
            std::cout << "Se va a mandar evento que no es quit" << std::endl;
            this->protocol.sendEvent(event);
        } else {
            std::cout << "Se va a mandar evento que es quit" << std::endl;
            this->protocol.sendEvent(event);
            return;
        }
    }
}

void EventSender::stop(void) {
    this->keep_runing = false;
}