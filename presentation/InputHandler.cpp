// InputHandler.cpp

#include "InputHandler.h"
#include "Renderer.h"
#include <conio.h>

char InputHandler::getUserInput() {
    return _getch();
}

KeyEnum InputHandler::processInput(char input) {
    if (input == -32 || input == 0) {
        char second = _getch();
        switch (second) {
        case 75: return KeyEnum::Left;
        case 77: return KeyEnum::Right;
        case 80: return KeyEnum::Down;
        case 72: return KeyEnum::Rotate;
        default: return KeyEnum::Down;
        }
    }
    if (input == ' ') return KeyEnum::HardDrop;
    return KeyEnum::Down;
}

int InputHandler::handleStageSelection(int currency) {
    int stageIndex = 0;
    while (true) {
        Renderer::drawSelectStage(stageIndex, currency);
        char input = getUserInput();

        if (input == '\r') break;

        KeyEnum key = processInput(input);
        if (key == KeyEnum::Right && stageIndex < 2) stageIndex++;
        else if (key == KeyEnum::Left && stageIndex > 0) stageIndex--;
    }
    return stageIndex + 1;
}

KeyEnum InputHandler::getKey() {
    return processInput(getUserInput());
}
