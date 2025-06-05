// Timer.h
#pragma once
#include <chrono>

class Timer {
private:
    int duration; // 총 제한 시간 (초)
    int elapsedTime; // 지난 시간 (초)
    std::chrono::steady_clock::time_point startTime; // 시작 시간 포인트
public:
    Timer();
    void start(int duration);
    void update();
    int getRemainingTime() const;
    bool isTimeUp() const;
};
