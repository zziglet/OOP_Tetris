// GameManager.cpp
#include "GameManager.h"
#include "Constants.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <conio.h>

GameManager::GameManager()
    : lives(Constants::INITIAL_LIVES),
    currency(0),
    isGameOver(false),
    currentStageIndex(0),
    currentBlock(nullptr),
    turnCount(0),
    blockGenerator(Stage(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::STAGE1_SUCCESS_SCORE, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN)) {

    stages.emplace_back(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::STAGE1_SUCCESS_SCORE, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
    stages.emplace_back(2, Constants::STAGE2_CURRENCY, Constants::STAGE2_DURATION, Constants::STAGE2_SPEED, Constants::STAGE2_SUCCESS_SCORE, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
    stages.emplace_back(3, Constants::STAGE3_CURRENCY, Constants::STAGE3_DURATION, Constants::STAGE3_SPEED, Constants::STAGE3_SUCCESS_SCORE, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
}

GameManager::~GameManager() {
    delete currentBlock;
    currentBlock = nullptr;
}

void GameManager::startGame() {
    renderer.showIntro();
    renderer.showStory();

    while (true) {
        int selected = inputHandler.handleStageSelection(currency);

        if (selected < 1 || selected > static_cast<int>(stages.size())) {
            renderer.showInsufficientCurrency(0);
            continue;
        }

        Stage& selectedStage = stages[selected - 1];
        int requiredCurrency = selectedStage.getCurrency();

        if (currency < requiredCurrency) {
            renderer.showInsufficientCurrency(requiredCurrency);
            continue;
        }

        renderer.showStageEntryConfirm(requiredCurrency);
        char confirm;
        std::cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') continue;

        currentStageIndex = selected - 1;
        currency -= requiredCurrency;

        runStage();

        isGameOver = false;
    }
}

void GameManager::runStage() {
    system("cls");
    Stage& stage = stages[currentStageIndex];
    board = Board();  // ���� �ʱ�ȭ
    scoreManager.reset();
    timer.start(stage.getDuration());
    turnCount = 0;
    blockGenerator = BlockGenerator(stage);
    spawnNewBlock();

    const int frameDelay = 20; // �Է� ������ ���� ����
    const int renderDelay = 200; // ȭ�� �׸��� ����

    int fallInterval = stage.getSpeed();
    auto lastFallTime = std::chrono::steady_clock::now();
    auto lastRenderTime = std::chrono::steady_clock::now();

    bool blockJustMerged = false;
    while (!timer.isTimeUp()) {
        if (isGameOver) {
            return;
        }

        timer.update();

        // Ű �Է� ������ ����
        if (_kbhit()) {
            char ch = _getch();
            KeyEnum key = inputHandler.processInput(ch);
            handleKeyInput(key);

            if (!board.getCurrentBlock()) {
                blockJustMerged = true;
            }
        }

        // �ڵ� ����
        auto now = std::chrono::steady_clock::now();
        auto elapsedFall = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();
        if (elapsedFall >= fallInterval) {
            Block* curr = board.getCurrentBlock();
            if (curr) {
                Block moved = *curr;
                moved.r += 1;

                if (board.canMove(moved)) {
                    board.moveBlock(KeyEnum::Down);
                }
                else {
                    board.mergeBlock();
                    blockJustMerged = true;
                }
            }
            lastFallTime = now;
        }

        // ȭ�� �������� ������ (������ ����)
        auto elapsedRender = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRenderTime).count();
        if (elapsedRender >= renderDelay) {
            renderer.drawBoard(board, scoreManager.getScore(), stage.getSuccessScore(), currentStageIndex + 1, timer.getRemainingTime(), lives);
            // renderer.drawScoreBar(scoreManager.getScore(), currency, timer.getRemainingTime());
            lastRenderTime = now;
        }

        // ��� ���� ó��
        if (blockJustMerged && !board.getCurrentBlock()) {
            auto cleared = board.checkClearedLines();
            board.clearLines(cleared);
            scoreManager.addScore(static_cast<int>(cleared.size()));
            turnCount++;
            spawnNewBlock();
            blockJustMerged = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));
    }

    // ���� ������ �ƴ� ��츸 Ŭ���� or ���� ����
    if (!isGameOver) {
        if (scoreManager.getScore() < stage.getSuccessScore()) {
            // Ÿ�̸� ���� + ���ھ� ���� �� ���� ó��
            handleFailure(false); // �Ϲ� ���з� ó��
        }
        else {
            handleClear(); // ����
        }
    }

}

void GameManager::handleKeyInput(KeyEnum key) {
    Block* curr = board.getCurrentBlock();

    if (!curr) return;  // ���� ���� ���¿��� �����ϸ� ����

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
        while (true) {
            //khj : �̰� deepcopy �ƴ��ٵ� �ǵ���� �۵��ϳ���?
            //jjw : �� ���θ����׿�.. �� �۵��ϱ� �մϴ�.
            Block next = *curr; // ���� �� ����
            next.r += 1;        // �Ʒ��� �� ĭ �̵� �õ�

            if (!board.canMove(next)) break;

            board.moveBlock(KeyEnum::Down);
            curr = board.getCurrentBlock(); // ���ŵ� �� ������ Ȯ��
            if (!curr) break;
        }
        board.mergeBlock();
        break;
    default:
        break;
    }
}

void GameManager::spawnNewBlock() {
    delete currentBlock;
    currentBlock = blockGenerator.getNextBlock(scoreManager.getScore(), turnCount);

    // �߾� ��� ��ġ ����
    currentBlock->r = 0;
    currentBlock->c = (Board::COLS - 4) / 2;
    currentBlock->setSpinCnt(0);

    // ��ȿ�� �˻� (��ü ������� �˻�)
    if (!board.canMove(*currentBlock)) {
        std::cout << "[DEBUG] canMove ����: ";
        std::cout << "r=" << currentBlock->r << ", c=" << currentBlock->c << std::endl;
        handleFailure(false);
        delete currentBlock;
        currentBlock = nullptr;
        return;
    }

    // board�� �������� ������
    board.setNextBlock(currentBlock, turnCount);

    //khj : �׷��� setNextBlock���� currentBlock�� ������ �����Ҵ� ������ �ϴ°� �Ѿ����� �ʳ���?
    //jjw : �� �¾ƿ� �Ҹ��ڿ� �ֱ� �ߴµ� ���⼭ �������ؾ��ұ��
    // GameManager�� �� �̻� �����͸� �������� ����
    // currentBlock = nullptr;
}


void GameManager::handleFailure(bool isExplosion) {
    if (isExplosion) {
        lives--; 
    }
    else {
        lives = 0;
    }

    if (lives <= 0) {
        currency = 0;
        isGameOver = true;
        renderer.showGameOver();
        return;
    }
}

void GameManager::handleClear() {
    int reward = 0;
    switch (currentStageIndex) {
    case 0:
        reward = Constants::STAGE1_SUCCESS_CURRENCY;
        break;
    case 1:
        reward = Constants::STAGE2_SUCCESS_CURRENCY;
        break;
    case 2:
        reward = Constants::STAGE3_SUCCESS_CURRENCY;
        break;
    default:
        reward = 0;
    }

    currency += reward;
    renderer.showStageClear(currentStageIndex, reward);
    if (currentStageIndex == static_cast<int>(stages.size()) - 1) {
        renderer.showEnding();
    }
    currentStageIndex++;
}

void GameManager::endGame() {
    renderer.showGameOver();
}
