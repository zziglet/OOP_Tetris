// ScoreManager.h
#pragma once

class ScoreManager {
private:
    int score;
    int currency;

public:
    ScoreManager();
    void addScore(int amount);
    void addCurrency(int amount);
    void reset();
    int getScore() const;
    int getCurrency() const;
};
