// Timer.h
#pragma once
#include <chrono>

class Timer {
private:
    int duration; // �� ���� �ð� (��)
    int elapsedTime; // ���� �ð� (��)
    std::chrono::steady_clock::time_point startTime; // ���� �ð� ����Ʈ
public:
    Timer();
    void start(int duration);
    void update();
    int getRemainingTime() const;
    bool isTimeUp() const;
};
