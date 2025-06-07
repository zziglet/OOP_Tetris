// GameManager.h
#pragma once

#include "../board/Board.h"
#include "../board/KeyEnum.h"
#include "../domain/BlockGenerator.h"
#include "../domain/ScoreManager.h"
#include "../presentation/Renderer.h"
#include "../presentation/InputHandler.h"
#include "./Timer.h"
#include "./Stage.h"
#include <vector>

class GameManager {
private:
    int lives;
    int explosion;
    int currency;
    bool isGameOver;
    int turnCount;
    int currentStageIndex;

    std::vector<Stage> stages;
    Timer timer;
    ScoreManager scoreManager;
    Board board;
    BlockGenerator blockGenerator;
    InputHandler inputHandler;
    Renderer renderer;

    shared_ptr<Block> currentBlock;

public:
    GameManager();
    ~GameManager();

    void startGame();
    void runStage();
    void handleFailure(bool isExplosion);
    void handleClear();
    void endGame();
    void spawnNewBlock();
    void handleKeyInput(KeyEnum key);
};

