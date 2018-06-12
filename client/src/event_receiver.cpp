#include "event_receiver.h"

#define TEAM_ID 1

EventReceiver::EventReceiver(Queue<Event> & events, ClientConfiguration & cfg, View::Camera & camera) :
events(events),
cfg(cfg),
camera(camera) {
    keep_runing = true;
}

bool EventReceiver::isRunning(void) const {
    return true;
}

size_t EventReceiver::getId(void) const {
    return 0;
}

void EventReceiver::run(void) {
    SDL_Event e;
    while (keep_runing) {
        while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				keep_runing = false;
			
			cfg.handleEvent(e);

			if (cfg.hasShooted()) {
				Event event(a_shoot, cfg.getSelectedWeapon(), TEAM_ID, cfg.getWeaponsCountdown(), cfg.getPowerShoot(), cfg.getSightAngle());
				events.push(event);
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					Event event(a_pointUp, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_s) {
					Event event(a_pointDown, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_a) {
					Event event(a_moveLeft, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_d) {
					Event event(a_moveRight, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_RETURN) {
					Event event(a_frontJump, TEAM_ID);
					events.push(event);
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE) {
					Event event(a_backJump, TEAM_ID);
					events.push(event);
				}

				if (e.key.keysym.sym == SDLK_LEFT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_UP) {
					camera.handleEvent(e);
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					camera.handleEvent(e);
				}
			}
		}

    }
}