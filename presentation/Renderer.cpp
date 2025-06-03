// Renderer.cpp
#pragma once

#include <conio.h>
#include <Windows.h>


#include "Renderer.h"
#include "Board.h"
#include "Block.h"
#include "Brick.h"

using namespace std;

void Renderer::drawSelectStage(int stage) {
    system("cls");
    std::cout << "===== SELECT STAGE =====" << std::endl;
    for (int i = 1; i <= 3; i++) {
        if (i == stage) cout << "> ";
        else cout << "  ";
        std::cout << " " << i << std::endl;
    }
    std::cout << "화살표 혹은 숫자키를 사용해 스테이지를 고르시오 (1~3)" << std::endl;
}

void Renderer::drawBoard(const Board& board) {
     

    auto grid = board.getGrid();

    for (int i = 4; i < board.ROWS; i++) {
        for (int j = 0; j < board.COLS; j++) {
            //cout << grid[i][j] << endl;
            //이런 느낌으로 하면 될듯.
            //느낌이 이렇다는거지 색깔 반영이나 등등 해야함
            cout << "";
        }
    }

}

void Renderer::drawScoreBar(int score, int stabilizer, int remainingTime) {
    std::cout << "Score: " << score << " | Stabilizer: " << stabilizer << " | Time Left: " << remainingTime << "s" << std::endl;
}

void Renderer::showStageClear(int stage, int stabilizer) {
    std::cout << "Stage " << stage << " Cleared!" << std::endl;
    std::cout << "You earned stabilizer: +" << stabilizer << std::endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void Renderer::showGameOver() {
    std::cout << "=========== GAME OVER ===========" << std::endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void Renderer::showIntro() {
    system("cls");
    string text = "*** GAME START ***";
    for (int i = 0; i < 3; i++) {
        std::cout << text << std::endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    std::cout << "Press ENTER to start..." << std::endl;
    cin.get();
}

void Renderer::showStory() {
    system("cls");
    gotoxy(10, 20);
    std::cout << "인류는 우주로 진출했지만, 인공위성 파편과 우주 쓰레기로 인해 지구 궤도가 망가졌다.\n"
        "임무는 간단하다: 하늘에서 떨어지는 구조 블록을 정확히 쌓아 궤도를 안정화시키자.\n"
        "하지만 블록 사이에 폭발물, 에너지 코어인 특수 요소들이 섞여 있어, 잘못 쌓으면 궤도가 불안정해지고 인류의 통신망이 무너진다!\n"
        "즉, 우주에서 지구를 향해 떨어지는 쓰레기들(블록)을 쌓아 없애기. 제한된 시간 안에 모든 쓰레기들을 쌓아 없애서 지구의 궤도를 안전하게 지키자!\n" << endl;
    std::cout << "\nPress ENTER to continue..." << std::endl;
    cin.get();
}

void Renderer::showInsufficientCurrency(int required) {
    std::cout << "\n[WARNING] 해당 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다." << std::endl;
    std::cout << "보유 스태빌라이저가 부족합니다. 다른 스테이지를 선택해주세요." << std::endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void Renderer::showStageEntryConfirm(int required) {
    std::cout << "\n이 스테이지 입장에는 " << required << " 스태빌라이저가 필요합니다. 입장하시겠습니까? (y/n): ";
}

//가고 싶은 x,y 위치로 감
int Renderer::gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = y;
    pos.X = x;
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

//출력 컬러 정하는 거
void Renderer::SetColor(int color)
{
    static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_output_handle, color);
}