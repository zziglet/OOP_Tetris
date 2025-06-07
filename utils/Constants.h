// Constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

// ANSI color codes
#define RESET         "\033[0m"
#define BOLD          "\033[1m"

#define BLACK         "\033[30m"
#define RED           "\033[31m"
#define GREEN         "\033[32m"
#define YELLOW        "\033[33m"
#define BLUE          "\033[34m"
#define MAGENTA       "\033[35m"
#define CYAN          "\033[36m"
#define WHITE         "\033[37m"

#define BRIGHT_BLACK  "\033[90m"
#define BRIGHT_RED    "\033[91m"
#define BRIGHT_GREEN  "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE   "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN   "\033[96m"
#define BRIGHT_WHITE  "\033[97m"


// Clear screen / move cursor
#define CLEAR_SCREEN "\033[2J"
#define CURSOR_HOME  "\033[H"

#endif // CONSTANTS_H

namespace Constants {
    // user 생명
    constexpr int INITIAL_LIVES = 3;

    // stage별 제한 시간
    constexpr int STAGE1_DURATION = 200;
    constexpr int STAGE2_DURATION = 200;
    constexpr int STAGE3_DURATION = 200;

    // stage별 필요 재화
    constexpr int STAGE1_CURRENCY = 0;
    constexpr int STAGE2_CURRENCY = 5;
    constexpr int STAGE3_CURRENCY = 10;

    // stage별 클리어 시 지급 재화
    constexpr int STAGE1_SUCCESS_CURRENCY = 8;
    constexpr int STAGE2_SUCCESS_CURRENCY = 13;
    constexpr int STAGE3_SUCCESS_CURRENCY = 30;

    // stage별 클리어 스코어 조건
    constexpr int STAGE1_SUCCESS_SCORE = 10000;
    constexpr int STAGE2_SUCCESS_SCORE = 15000;
    constexpr int STAGE3_SUCCESS_SCORE = 20000;

    // stage별 게임 진행 속도
    constexpr int STAGE1_SPEED = 1000;
    constexpr int STAGE2_SPEED = 800;
    constexpr int STAGE3_SPEED = 500;

    // 게임 매니저 변수
    constexpr int CLEAR_LINES_SCORE = 1000;
    constexpr int NEW_BLOCK_SCORE = 300;

    constexpr int STAGE1_BOMB_SCORE_THRESHOLD = 4000;
    constexpr int STAGE1_ENERGY_CORE_THRESHOLD = 2000;

    constexpr int STAGE2_BOMB_SCORE_THRESHOLD = 3000;
    constexpr int STAGE2_ENERGY_CORE_THRESHOLD = 3000;

    constexpr int STAGE3_BOMB_SCORE_THRESHOLD = 2000;
    constexpr int STAGE3_ENERGY_CORE_THRESHOLD = 4000;
}