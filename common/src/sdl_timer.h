#ifndef __SDL_TIMER_H__
#define __SDL_TIMER_H__

#include <SDL2/SDL.h>

// fuente: http://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php

class Timer {
  private:
    //The clock time when the timer started
    int mStartTicks;

    //The ticks stored when the timer was paused
    int mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

  public:
    //Initializes variables
    Timer();
    ~Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    size_t getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
};

#endif
