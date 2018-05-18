#include <iostream>
#include <string>
#include "socket.h"
#include "event_sender.h"
#include "blocking_queue.h"
#include "thread.h"
#include "protocol.h"

EventSender::EventSender(Protocol & p, BlockingQueue<char> & e) :
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
    char c;
    while (keep_runing) {
        c = this->events.pop();
        std::cout << "Soy el hilo sender, el evento popeado es: " << c << std::endl;
        this->protocol.sendEvent(c);
    }
}

void EventSender::stop(void) {
    this->keep_runing = false;
}