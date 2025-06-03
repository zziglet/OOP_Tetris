// Timer.h
#pragma once
#include <chrono>

class Timer {
private:
    int startTime;      // 제한 시간 (초)
    int elapsedTime;    // 경과 시간 (초)
    std::chrono::time_point<std::chrono::steady_clock> startPoint;

public:
    Timer();                // 기본 생성자
    void start(int duration); // 타이머 시작 (duration초로 초기화)
    void update();          // 경과 시간 갱신

    int getRemainingTime() const; // 남은 시간 반환
    bool isTimeUp() const;        // 제한 시간 초과 여부
};
