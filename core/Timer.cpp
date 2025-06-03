// Timer.cpp
#include "Timer.h"

Timer::Timer()
    : startTime(0), elapsedTime(0) {}

void Timer::start(int duration) {
    startTime = duration;
    elapsedTime = 0;
    startPoint = std::chrono::steady_clock::now();
}

void Timer::update() {
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startPoint).count();
}

int Timer::getRemainingTime() const {
    int remaining = startTime - elapsedTime;
    return remaining > 0 ? remaining : 0;
}

bool Timer::isTimeUp() const {
    return elapsedTime >= startTime;
}
