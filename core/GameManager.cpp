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
    explosion(0),
    isGameOver(false),
    currentStageIndex(0),
    currentBlock(nullptr),
    turnCount(0),
    blockGenerator(Stage(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::STAGE1_SUCCESS_SCORE, Constants::STAGE1_BOMB_SCORE_THRESHOLD, Constants::STAGE1_ENERGY_CORE_THRESHOLD)) {

    stages.emplace_back(1, Constants::STAGE1_CURRENCY, Constants::STAGE1_DURATION, Constants::STAGE1_SPEED, Constants::STAGE1_SUCCESS_SCORE, Constants::STAGE1_BOMB_SCORE_THRESHOLD, Constants::STAGE1_ENERGY_CORE_THRESHOLD);
    stages.emplace_back(2, Constants::STAGE2_CURRENCY, Constants::STAGE2_DURATION, Constants::STAGE2_SPEED, Constants::STAGE2_SUCCESS_SCORE, Constants::STAGE2_BOMB_SCORE_THRESHOLD, Constants::STAGE2_ENERGY_CORE_THRESHOLD);
    stages.emplace_back(3, Constants::STAGE3_CURRENCY, Constants::STAGE3_DURATION, Constants::STAGE3_SPEED, Constants::STAGE3_SUCCESS_SCORE, Constants::STAGE3_BOMB_SCORE_THRESHOLD, Constants::STAGE3_ENERGY_CORE_THRESHOLD);
}

GameManager::~GameManager() {
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
    board = Board();  // 보드 초기화
    scoreManager.reset();
    timer.start(stage.getDuration());
    turnCount = 0;
    explosion = 0;
    blockGenerator = BlockGenerator(stage);
    spawnNewBlock();

    const int frameDelay = 20; // 입력 감지용 빠른 루프
    const int renderDelay = 200; // 화면 그리는 간격

    int fallInterval = stage.getSpeed();
    auto lastFallTime = std::chrono::steady_clock::now();
    auto lastRenderTime = std::chrono::steady_clock::now();

    bool blockJustMerged = false;
    cout << CLEAR_SCREEN;
    renderer.drawGame(board, scoreManager.getScore(), stage.getSuccessScore(), currentStageIndex + 1, timer.getRemainingTime(), lives);

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
            shared_ptr<Block> curr = board.getCurrentBlock();
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
            renderer.drawGame(board, scoreManager.getScore(), stage.getSuccessScore(), currentStageIndex + 1, timer.getRemainingTime(), lives);
            // renderer.drawScoreBar(scoreManager.getScore(), currency, timer.getRemainingTime());
            lastRenderTime = now;
        }

        // 블록 병합 처리
        if (blockJustMerged && !board.getCurrentBlock()) {
            auto cleared = board.checkClearedLines();
            board.clearLines(cleared);
            int baseScore = static_cast<int>(cleared.size() * Constants::CLEAR_LINES_SCORE);
            int bonus = 0;

            if (cleared.size() >= 2) {
                bonus = static_cast<int>(cleared.size() * cleared.size() * 100);
            }
            scoreManager.addScore(baseScore + bonus);
            turnCount++;
            spawnNewBlock();
            scoreManager.addScore(Constants::NEW_BLOCK_SCORE);
            blockJustMerged = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));
    }

    // 게임 오버가 아닌 경우만 클리어 or 실패 판정
    if (!isGameOver) {
        if (scoreManager.getScore() < stage.getSuccessScore()) {
            // 타이머 종료 + 스코어 부족 → 실패 처리
            handleFailure(false); // 일반 실패로 처리
        }
        else {
            handleClear(); // 성공
        }
    }

}

void GameManager::handleKeyInput(KeyEnum key) {
    shared_ptr<Block> curr = board.getCurrentBlock();

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
    
    currentBlock = blockGenerator.getNextBlock(scoreManager.getScore());

    // 중앙 상단 위치 지정
    currentBlock->r = 0;
    currentBlock->c = (Board::COLS - 4) / 2;
    currentBlock->setSpinCnt(0);

    // 유효성 검사 (객체 기반으로 검사)
    if (!board.canMove(*currentBlock)) {
        std::cout << "[DEBUG] canMove 실패: ";
        std::cout << "r=" << currentBlock->r << ", c=" << currentBlock->c << std::endl;
        handleFailure(false);
        currentBlock = nullptr;
        return;
    }

    bool exploded = board.setNextBlock(currentBlock, turnCount);
    if (exploded) {
        handleFailure(true);  // 폭탄으로 인한 실패
    }

    // board가 소유권을 가져감
    board.setNextBlock(currentBlock, turnCount);

    // GameManager는 더 이상 포인터를 유지하지 않음
    // currentBlock = nullptr;
}


void GameManager::handleFailure(bool isExplosion) {
    if (isGameOver) return;  // 이미 게임 오버면 중복 처리 방지

    if (isExplosion) {
        explosion++;  // 누적 폭발 수 증가

        if (explosion >= 3) {
            lives = 0;
            currency = 0;
            isGameOver = true;
            renderer.showGameOver();
        }
        else {
            lives--; // 생명도 1 감소
            if (lives <= 0) {
                isGameOver = true;
                renderer.showGameOver();
            }
        }
    }
    else {
        lives = 0; // 천장 닿거나 시간 초과는 즉사
        isGameOver = true;
        renderer.showGameOver();
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
    renderer.showStageClear(currentStageIndex, reward, scoreManager.getScore());
    if (currentStageIndex == static_cast<int>(stages.size()) - 1) {
        renderer.showEnding();
    }
    currentStageIndex++;
}

void GameManager::endGame() {
    renderer.showGameOver();
}
