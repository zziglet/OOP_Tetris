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
    void drawScoreBar(int score, int currency, int remainingTime);
    void showStageClear(int stage, int currency);
    void showGameOver();
    void showIntro();
    void showStory();
    void showInsufficientCurrency(int required);
    void showStageEntryConfirm(int required);
};
