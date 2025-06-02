// Renderer.cpp
#include "Renderer.h"
using namespace std;

void Renderer::drawSelectStage(int stage) {
    system("cls");
    cout << "===== SELECT STAGE =====" << endl;
    for (int i = 1; i <= 3; i++) {
        if (i == stage) cout << "> ";
        else cout << "  ";
        cout << " " << i << endl;
    }
    cout << "화살표 혹은 숫자키를 사용해 스테이지를 고르시오 (1~3)" << endl;
}

// void Renderer::drawBoard(const Board& board) {
//     board.render();
// }

void Renderer::drawScoreBar(int score, int stabilizer, int remainingTime) {
    cout << "Score: " << score << " | Stabilizer: " << stabilizer << " | Time Left: " << remainingTime << "s" << endl;
}

void Renderer::showStageClear(int stage, int stabilizer) {
    cout << "Stage " << stage << " Cleared!" << endl;
    cout << "You earned stabilizer: +" << stabilizer << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void Renderer::showGameOver() {
    cout << "=========== GAME OVER ===========" << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void Renderer::showIntro() {
    system("cls");
    string text = "*** GAME START ***";
    for (int i = 0; i < 3; i++) {
        cout << text << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "Press ENTER to start..." << endl;
    cin.get();
}

void Renderer::showStory() {
    system("cls");
    cout << "인류는 우주로 진출했지만, 인공위성 파편과 우주 쓰레기로 인해 지구 궤도가 망가졌다.\n"
        "임무는 간단하다: 하늘에서 떨어지는 구조 블록을 정확히 쌓아 궤도를 안정화시키자.\n"
        "하지만 블록 사이에 폭발물, 에너지 코어인 특수 요소들이 섞여 있어, 잘못 쌓으면 궤도가 불안정해지고 인류의 통신망이 무너진다!\n"
        "즉, 우주에서 지구를 향해 떨어지는 쓰레기들(블록)을 쌓아 없애기. 제한된 시간 안에 모든 쓰레기들을 쌓아 없애서 지구의 궤도를 안전하게 지키자!\n" << endl;
    cout << "\nPress ENTER to continue..." << endl;
    cin.get();
}

void Renderer::showInsufficientCurrency(int required) {
    cout << "\n[WARNING] 해당 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다." << endl;
    cout << "보유 스태빌라이저가 부족합니다. 다른 스테이지를 선택해주세요." << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void Renderer::showStageEntryConfirm(int required) {
    cout << "\n이 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다. 입장하시겠습니까? (y/n): ";
}
