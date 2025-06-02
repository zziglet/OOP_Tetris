// ScoreManager.cpp
#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), currency(0) {}

void ScoreManager::addScore(int amount) {
    score += amount;
}

void ScoreManager::addCurrency(int amount) {
    currency += amount;
}

void ScoreManager::reset() {
    score = 0;
    currency = 0;
}

int ScoreManager::getScore() const {
    return score;
}

int ScoreManager::getCurrency() const {
    return currency;
}
