// Renderer.h
#pragma once
#include <string>
#include <vector>

class Renderer {
public:
    void showMainMenu();
    void showStageSelect(int coin);
    void showGameScreen(const std::vector<std::string>& boardView, int score, int coin);
    void showScore(int score, int coin);
    void showStageResult(bool success, int earnedCoin);
    void showEnding();
    void showMessage(const std::string& message);
};
