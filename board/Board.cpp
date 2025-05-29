// board.cpp
#include "Board.h"
#include <iostream>

Board::Board() {
    // Initialize all cells to EmptyBrick
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }
    currentBlock = nullptr; //  GameManager가 해도 되는 부분
}

int Board::clearFullLines() {
    int cleared = 0;
    for (int i = 0; i < ROWS; ++i) {
        bool full = true;
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j].getBrickType() == BrickEnum::EmptyBrick) {
                full = false;
                break;
            }
        }
        if (full) {
            ++cleared;
            // 모든 줄을 하나씩 내리기
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < COLS; ++j) {
                    grid[k][j] = grid[k - 1][j];
                }
            }
            // 윗줄 제거
            for (int j = 0; j < COLS; ++j) {
                grid[0][j] = Brick(BrickEnum::EmptyBrick);
            }
        }
    }
    return cleared;
}

bool Board::isGameOver() {
    for (int j = 0; j < COLS; ++j) {
        if (grid[0][j].getBrickType() != BrickEnum::EmptyBrick) {
            return true;
        }
    }
    return false;
}

void Board::moveBlock(KeyEnum key) {
    // Placeholder: update logic with currentBlock movement based on key
    // Assume currentBlock is non-null and move it within grid boundaries
    // Then call mergeBlock if needed
}

void Board::mergeBlock() {
    // Placeholder: integrate currentBlock into grid and possibly trigger special effects
    // Check for explosive or energy blocks and call appropriate methods
}

void Board::triggerEnergyCore(int startRow, int endRow) {
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }
}

void Board::triggerBomb() {
    // Placeholder: determine bomb position and clear a 3x3 area or similar
}

void Board::render() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << static_cast<int>(grid[i][j].getBrickType()) << " ";
        }
        std::cout << std::endl;
    }
}
