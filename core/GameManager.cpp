// GameManager.cpp
#include "GameManager.h"
#include <thread>
#include <chrono>
#include <iostream>

GameManager::GameManager()
    : lives(3), currency(10), isGameOver(false), currentStageIndex(0), currentBlock(nullptr), turnCount(0), blockGenerator(Stage(1, 60, 500, 100, 20))
{
    stages.emplace_back(1, 60, 500, 100, 20);
    stages.emplace_back(2, 70, 400, 150, 15);
    stages.emplace_back(3, 90, 300, 200, 10);
}

GameManager::~GameManager() {
    delete currentBlock;
}

void GameManager::startGame() {
    renderer.showIntro();     // ��Ʈ�� ���
    renderer.showStory();     // ���� ���丮 ���

    while (!isGameOver && currentStageIndex < stages.size()) {
        runStage();
    }

    endGame();
}


void GameManager::runStage() {
    Stage& stage = stages[currentStageIndex];
    board = Board(); // ���� �ʱ�ȭ
    timer.start(stage.getDuration()); // ����
    turnCount = 0;

    blockGenerator = BlockGenerator(stage);
    spawnNewBlock();

    while (!timer.isTimeUp()) { // ����
        timer.update(); // ����

        renderer.drawBoard(board);
        renderer.drawScoreBar(scoreManager.getScore(), currency, timer.getRemainingTime());
        KeyEnum key = inputHandler.getKey();
        switch (key) {
        case KeyEnum::Left:
        case KeyEnum::Right:
        case KeyEnum::Down:
            board.moveBlock(key);
            break;
        case KeyEnum::Rotate:
            board.rotateBlock();
            break;
        case KeyEnum::HardDrop:
            while (board.canMove(
                board.getCurrentBlock()->r + 1,
                board.getCurrentBlock()->c,
                board.getCurrentBlock()->getSpinCnt()))
            {
                board.moveBlock(KeyEnum::Down);
            }
            board.mergeBlock();
            break;
        default:
            break;
        }


        if (!board.canMove(
            board.getCurrentBlock()->r + 1,
            board.getCurrentBlock()->c,
            board.getCurrentBlock()->getSpinCnt()))
        {
            board.mergeBlock();
            auto cleared = board.checkClearedLines();
            board.clearLines(cleared);
            scoreManager.addScore(static_cast<int>(cleared.size()));
            turnCount++;
            spawnNewBlock();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(stage.getSpeed()));
    }

    handleClear();
}

void GameManager::spawnNewBlock() {
    delete currentBlock;
    currentBlock = blockGenerator.getNextBlock(scoreManager.getScore(), turnCount);

    // ������ ����� ��ġ���� ���� �� �ִ��� Ȯ��
    if (!board.canMove(currentBlock->r, currentBlock->c, currentBlock->getSpinCnt())) {
        handleFailure();
        return;
    }

    board.setNextBlock(currentBlock, turnCount);
}


void GameManager::handleFailure() {
    lives--;
    if (lives <= 0) {
        isGameOver = true;
    }
    renderer.showGameOver();
}

void GameManager::handleClear() {
    int reward = 5 + currentStageIndex * 3;
    currency += reward;
    currentStageIndex++;
    renderer.showStageClear(currentStageIndex, reward);
}

void GameManager::endGame() {
    renderer.showGameOver();
}
