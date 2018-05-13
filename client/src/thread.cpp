#include "thread.h"

Thread::Thread(void) {
}

Thread::Thread(Thread && other_moved) {
    this->thread = std::move(other_moved.thread);
}

Thread & Thread::operator=(Thread && other_copyed) {
    this->thread = std::move(other_copyed.thread);
    return * this;
}

Thread::~Thread(void) {
}

void Thread::join(void) {
    this->thread.join();
}

void Thread::start(void) {
    this->thread = std::thread(&Thread::run, this);
}
