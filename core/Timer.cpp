// Timer.cpp
#include "Timer.h"

Timer::Timer()
    : duration(0), elapsedTime(0) {}

void Timer::start(int duration) {
    this->duration = duration;
    elapsedTime = 0;
    startTime = std::chrono::steady_clock::now();
}

void Timer::update() {
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
}

int Timer::getRemainingTime() const {
    int remaining = duration - elapsedTime;
    return remaining > 0 ? remaining : 0;
}

bool Timer::isTimeUp() const {
    return elapsedTime >= duration;
}
