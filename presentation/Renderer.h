// Renderer.h
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "Board.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class Renderer {
public:
    static void gotoXY(int x, int y);
    static void drawSelectStage(int stageIndex);
    static void drawBoard(const Board& board);
    static void drawScoreBar(int score, int stabilizer, int remainingTime);
    static void showStageClear(int stage, int stabilizer);
    static void showGameOver();
    static void showIntro();
    static void showStory();
    static void showInsufficientCurrency(int required);
    static void showStageEntryConfirm(int required);
};
