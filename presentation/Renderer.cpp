// Renderer.cpp
#include "Renderer.h"
#include <iostream>
using namespace std;

void Renderer::showMainMenu() {
    cout << "===============================" << endl;
    cout << "       [우주 쓰레기 정화작전]       " << endl;
    cout << "===============================" << endl;
    cout << " 1. 게임 시작" << endl;
    cout << " 2. 종료" << endl;
    cout << "===============================" << endl;
}

void Renderer::showStageSelect(int coin) {
    cout << "\n현재 재화: " << coin << "코인" << endl;
    cout << "입장할 스테이지를 선택하세요 (1~3): ";
}

void Renderer::showGameScreen(const vector<string>& boardView, int score, int coin) {
    system("clear");  // 터미널 화면 정리 (Windows는 system("cls"))
    cout << "[Score: " << score << " | Coin: " << coin << "]" << endl;
    for (const auto& row : boardView) {
        cout << row << endl;
    }
}

void Renderer::showScore(int score, int coin) {
    cout << "현재 점수: " << score << ", 보유 재화: " << coin << endl;
}

void Renderer::showStageResult(bool success, int earnedCoin) {
    if (success) {
        cout << "\n[스테이지 클리어!]" << endl;
        cout << "획득 재화: " << earnedCoin << " 코인\n" << endl;
    } else {
        cout << "\n[스테이지 실패...]" << endl;
        cout << "획득한 재화는 초기화됩니다.\n" << endl;
    }
}

void Renderer::showEnding() {
    cout << "===============================" << endl;
    cout << " 인류는 지구 궤도를 안정화시켰다!" << endl;
    cout << "   통신망은 회복되었고, 우주는" << endl;
    cout << "   다시 평화를 되찾았다.." << endl;
    cout << "===============================" << endl;
}

void Renderer::showMessage(const string& message) {
    cout << message << endl;
}
