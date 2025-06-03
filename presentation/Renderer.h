//Renderer.h
#pragma once
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>

class Renderer {
public:
    void drawSelectStage(int stage);
    void drawBoard(const Board& board);
    void drawScoreBar(int score, int stabilizer, int remainingTime); //stabilizer(안정시켜주는 장치?) = 재화
    void showStageClear(int stage, int stabilizer);
    void showGameOver();
    void showIntro();
    void showStory();
    void showInsufficientCurrency(int required);
    void showStageEntryConfirm(int required);
    int gotoxy(int x, int y);
    void SetColor(int color);
};
