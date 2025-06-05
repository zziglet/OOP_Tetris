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
    constexpr int INITIAL_LIVES = 3;
    constexpr int STAGE1_DURATION = 120;
    constexpr int STAGE2_DURATION = 90;
    constexpr int STAGE3_DURATION = 60;
    constexpr int STAGE1_CURRENCY = 0;
    constexpr int STAGE2_CURRENCY = 5;
    constexpr int STAGE3_CURRENCY = 10;
    constexpr int STAGE1_SUCCESS_SCORE = 5;
    constexpr int STAGE2_SUCCESS_SCORE = 7;
    constexpr int STAGE3_SUCCESS_SCORE = 9;
    constexpr int STAGE1_SPEED = 1000;
    constexpr int STAGE2_SPEED = 800;
    constexpr int STAGE3_SPEED = 500;
    constexpr int BOMB_SCORE_THRESHOLD = 5000;
    constexpr int ENERGY_CORE_TURN = 6;
}