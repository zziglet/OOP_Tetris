// Renderer.cpp
#include "Renderer.h"

void Renderer::gotoXY(int x, int y) {
#ifdef _WIN32
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y + 1, x + 1);
#endif
}

void Renderer::drawSelectStage(int stageIndex) {
    system("cls");
    std::cout << "===== SELECT STAGE =====" << std::endl;
    std::cout << "    1    2    3" << std::endl;
    gotoXY(4 + stageIndex * 6, 2); // 화살표 출력 위치
    std::cout << "  ↑" << std::endl;
    gotoXY(0, 4);
    std::cout << "화살표 ← →로 이동, ENTER로 선택" << std::endl;
}

void Renderer::drawBoard(const Board& board) {
    Renderer::gotoXY(0, 5);
    const auto& grid = board.getGrid();
    for (int i = 4; i < 22; ++i) { // 상단 4줄은 출력 안 함
        for (int j = 0; j < 12; ++j) {
            BrickEnum type = grid[i][j].getBrickType();
            if (type == BrickEnum::EmptyBrick) std::cout << "□ ";
            else if (type == BrickEnum::BombBrick) std::cout << "B ";
            else if (type == BrickEnum::EnergyBrick) std::cout << "E ";
            else std::cout << "■ ";
        }
        std::cout << std::endl;
    }
}

void Renderer::drawScoreBar(int score, int stabilizer, int remainingTime) {
    gotoXY(0, 0);
    std::cout << "Score: " << score << " | Stabilizer: " << stabilizer << " | Time Left: " << remainingTime << "s" << std::endl;
}

void Renderer::showStageClear(int stage, int stabilizer) {
    gotoXY(0, 30);
    std::cout << "Stage " << stage << " Cleared!" << std::endl;
    std::cout << "You earned stabilizer: +" << stabilizer << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Renderer::showGameOver() {
    gotoXY(0, 30);
    std::cout << "=========== GAME OVER ===========" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Renderer::showIntro() {
    system("cls");
    std::string text = "*** GAME START ***";
    for (int i = 0; i < 3; i++) {
        gotoXY(10, 10);
        std::cout << text << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("cls");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Press ENTER to start..." << std::endl;
    std::cin.get();
}

void Renderer::showStory() {
    system("cls");
    std::cout << "인류는 우주로 진출했지만, 인공위성 파편과 우주 쓰레기로 인해 지구 궤도가 망가졌다.\n"
        << "임무는 간단하다: 하늘에서 떨어지는 구조 블록을 정확히 쌓아 궤도를 안정화시키자.\n"
        << "하지만 블록 사이에 폭발물, 에너지 코어인 특수 요소들이 섞여 있어, 잘못 쌓으면 궤도가 불안정해지고 인류의 통신망이 무너진다!\n"
        << "즉, 우주에서 지구를 향해 떨어지는 쓰레기들(블록)을 쌓아 없애기. 제한된 시간 안에 모든 쓰레기들을 쌓아 없애서 지구의 궤도를 안전하게 지키자!\n" << std::endl;
    std::cout << "\nPress ENTER to continue..." << std::endl;
    std::cin.get();
}

void Renderer::showInsufficientCurrency(int required) {
    std::cout << "\n[WARNING] 해당 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다." << std::endl;
    std::cout << "보유 스태빌라이저가 부족합니다. 다른 스테이지를 선택해주세요." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Renderer::showStageEntryConfirm(int required) {
    std::cout << "\n이 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다. 입장하시겠습니까? (y/n): ";
}
