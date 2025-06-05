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
    board = Board();  // 보드 초기화
    scoreManager.reset();
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
        if (isGameOver) {
            return;
        }

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
            renderer.drawBoard(board, scoreManager.getScore(), stage.getSuccessScore(), currentStageIndex + 1, timer.getRemainingTime(), lives);
            // renderer.drawScoreBar(scoreManager.getScore(), currency, timer.getRemainingTime());
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
            //khj : 이거 deepcopy 아닐텐데 의도대로 작동하나요?
            //jjw : 헉 저두몰랐네요.. 잘 작동하긴 합니다.
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
        handleFailure(false);
        delete currentBlock;
        currentBlock = nullptr;
        return;
    }

    // board가 소유권을 가져감
    board.setNextBlock(currentBlock, turnCount);

    //khj : 그러면 setNextBlock에서 currentBlock이 들어오면 동적할당 릴리즈 하는거 켜야하지 않나요?
    //jjw : 아 맞아요 소멸자에 넣긴 했는데 여기서 릴리즈해야할까요
    // GameManager는 더 이상 포인터를 유지하지 않음
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
