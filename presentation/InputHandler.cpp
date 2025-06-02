// InputHandler.cpp
#include "InputHandler.h"
#include <conio.h>

char InputHandler::getUserInput() {
    return _getch();
}

KeyEnum InputHandler::processInput(char input) {
    if (input == -32 || input == 0) {
        char second = _getch();
        switch (second) {
        case 80: return KeyEnum::Down;    // ↓
        case 75: return KeyEnum::Left;    // ←
        case 77: return KeyEnum::Right;   // →
        case 72: return KeyEnum::Rotate;  // ↑: 회전
        default: return KeyEnum::Down;    // 예외 입력은 무시 또는 기본값
        }
    }
    if (input == ' ') return KeyEnum::HardDrop; // 스페이스바
    return KeyEnum::Down; // 방향키 외 입력은 무시 또는 기본값
}
