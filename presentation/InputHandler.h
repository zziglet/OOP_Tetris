// InputHandler.h
#pragma once
#include "KeyEnum.h"

class InputHandler {
public:
    static char getUserInput();
    static KeyEnum processInput(char input);
    static int handleStageSelection();
};
