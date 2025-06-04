// GameManager.cpp
#include "GameManager.h"
#include "Constants.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <conio.h>

GameManager::GameManager()
    : lives(Constants::INITIAL_LIVES),
    currency(10),
    isGameOver(false),
    currentStageIndex(0),
    currentBlock(nullptr),
    turnCount(0),
    blockGenerator(Stage(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN)) {

    stages.emplace_back(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
    stages.emplace_back(2, Constants::STAGE2_CURRENCY, Constants::STAGE2_DURATION, Constants::STAGE2_SPEED, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
    stages.emplace_back(3, Constants::STAGE3_CURRENCY, Constants::STAGE3_DURATION, Constants::STAGE3_SPEED, Constants::BOMB_SCORE_THRESHOLD, Constants::ENERGY_CORE_TURN);
}

GameManager::~GameManager() {
    delete currentBlock;
}

void GameManager::startGame() {
    renderer.showIntro();
    renderer.showStory();

    while (!isGameOver) {
        int selected = inputHandler.handleStageSelection();

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

        if (isGameOver || currentStageIndex >= static_cast<int>(stages.size())) break;
    }

    endGame();
}

void GameManager::runStage() {
    Stage& stage = stages[currentStageIndex];
    board = Board();  // 보드 초기화
    timer.start(stage.getDuration());
    turnCount = 0;
    blockGenerator = BlockGenerator(stage);
    spawnNewBlock();

    const int frameDelay = 20; // 입력 감지용 빠른 루프
    const int renderDelay = 200; // 화면 그리는 간격

    int fallInterval = stage.getSpeed();
    auto lastFallTime = std::chrono::steady_clock::now();
    auto lastRenderTime = std::chrono::steady_clock::now();

    bool blockJustMerged = false;
    while (!timer.isTimeUp()) {
        timer.update();

        // 키 입력 빠르게 감지
        if (_kbhit()) {
            char ch = _getch();
            KeyEnum key = inputHandler.processInput(ch);
            handleKeyInput(key);

            if (!board.getCurrentBlock()) {
                blockJustMerged = true;
            }
        }

        // 자동 낙하
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

        // 화면 렌더링은 느리게 (깜빡임 방지)
        auto elapsedRender = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRenderTime).count();
        if (elapsedRender >= renderDelay) {
            renderer.drawBoard(board);
            renderer.drawScoreBar(scoreManager.getScore(), currency, timer.getRemainingTime());
            lastRenderTime = now;
        }

        // 블록 병합 처리
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

    handleClear();
}


void GameManager::handleKeyInput(KeyEnum key) {
    Block* curr = board.getCurrentBlock();

    if (!curr) return;  // 블럭이 없는 상태에서 조작하면 무시

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
            Block next = *curr; // 현재 블럭 복사
            next.r += 1;        // 아래로 한 칸 이동 시도

            if (!board.canMove(next)) break;

            board.moveBlock(KeyEnum::Down);
            curr = board.getCurrentBlock(); // 갱신된 블럭 포인터 확인
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

    // 중앙 상단 위치 지정
    currentBlock->r = 0;
    currentBlock->c = (Board::COLS - 4) / 2;
    currentBlock->setSpinCnt(0);

    // 유효성 검사 (객체 기반으로 검사)
    if (!board.canMove(*currentBlock)) {
        std::cout << "[DEBUG] canMove 실패: ";
        std::cout << "r=" << currentBlock->r << ", c=" << currentBlock->c << std::endl;
        handleFailure();
        delete currentBlock;
        currentBlock = nullptr;
        return;
    }

    // board가 소유권을 가져감
    board.setNextBlock(currentBlock, turnCount);

    // GameManager는 더 이상 포인터를 유지하지 않음
    currentBlock = nullptr;
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
