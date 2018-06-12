#include "event_receiver.h"
#include "protocol.h"
#include "event.h"
#include "match.h"

EventReceiver::EventReceiver(Client * cli, World & w, Match & match, size_t id) :
client(cli),
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
        Event new_event = this->client->rcvEvent();
        if (new_event.quit()) {
            std::cout << "Recibido evento de quit." << std::endl;
            this->quit_event = true;
            stop();
            return;
        }
        size_t team_turn = match.getTeamTurn();
        if (match.getTurnTimeleft() > 0 && team_turn == new_event.getTeamId()) {
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
