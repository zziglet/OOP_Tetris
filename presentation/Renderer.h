// -*- coding: utf-8 -*-
// Renderer.h
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "Board.h"

class Renderer {
public:
    static void gotoXY(int x, int y);
    static void drawSelectStage(int stageIndex, int currency);
    static void drawGame(const Board& board, int score, int targetScore, int stage, int remainingTime, int lives);
    static void showStageClear(int stage, int stabilizer, int score);
    static void showGameOver();
    static void showIntro();
    static void showStory();
    static void showInsufficientCurrency(int required);
    static void showStageEntryConfirm(int required);
    static void showEnding();
    static void clearLine(const Board& board, int row);
};
