// InputHandler.h

#pragma once

#include "KeyEnum.h"

class InputHandler {
public:
    char getUserInput();
    KeyEnum processInput(char input);
    KeyEnum getKey();
    int handleStageSelection(int currency);
};
