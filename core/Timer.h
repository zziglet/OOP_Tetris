// Timer.h
#pragma once
#include <chrono>

class Timer {
private:
    int startTime;      // ���� �ð� (��)
    int elapsedTime;    // ��� �ð� (��)
    std::chrono::time_point<std::chrono::steady_clock> startPoint;

public:
    Timer();                // �⺻ ������
    void start(int duration); // Ÿ�̸� ���� (duration�ʷ� �ʱ�ȭ)
    void update();          // ��� �ð� ����

    int getRemainingTime() const; // ���� �ð� ��ȯ
    bool isTimeUp() const;        // ���� �ð� �ʰ� ����
};
