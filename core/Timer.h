// Timer.h
#pragma once
#include <chrono>

class Timer {
private:
    int duration;
    int elapsedTime;
    std::chrono::steady_clock::time_point startTime;
public:
    Timer();
    void start(int duration);
    void update();
    int getRemainingTime() const;
    bool isTimeUp() const;
};
