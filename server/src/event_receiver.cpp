#include "event_receiver.h"
#include "protocol.h"
#include "event.h"
#include "match.h"

EventReceiver::EventReceiver(Protocol & prt, World & w, Match & match, size_t id) :
protocol(prt),
world(w),
match(match),
team_id(id) {
    this->keep_running = true;
    this->quit_event = false;
}

bool EventReceiver::isRunning(void) const {
    return this->keep_running;
}

size_t EventReceiver::getId(void) const {
    return this->team_id;
}

void EventReceiver::run(void) {
    while (keep_running) {
        Event new_event = this->protocol.rcvEvent();
        if (new_event.quit()) {
            this->quit_event = true;
            stop();
            return;
        }
        int team_turn = match.getTeamTurn();
        if (match.getTurnTimeleft() > 0) {
            if (match.extraTime() && new_event.getNode()["event"]["action"].as<int>() == a_shoot) {
                continue;
            }
            this->world.executeAction(new_event, match.getWormTurn(team_turn));            
        }
    }
}

bool EventReceiver::quitEvent(void) {
    return this->quit_event;
}

void EventReceiver::stop(void) {
    this->keep_running = false;
}
