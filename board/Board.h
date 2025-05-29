// board.h
#pragma once
#include "Brick.h"
#include "Block.h"
#include "KeyEnum.h"

class Board {
private:
    static const int ROWS = 22;
    static const int COLS = 12;
    Brick grid[ROWS][COLS];
    Block* currentBlock;

    void mergeBlock();
    bool canMove(int r, int c, int spin);
    void triggerEnergyCore(int startRow, int endRow);
    void triggerBomb();

public:
    Board();

    int clearFullLines();
    bool isGameOver();
    void moveBlock(KeyEnum key);

    void render();
};