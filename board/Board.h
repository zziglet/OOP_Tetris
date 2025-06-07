// board.h
#pragma once
#include "Brick.h"
#include "Block.h"
#include "KeyEnum.h"
#include "list"

#include <memory>

using namespace std;

class Board {
public:
    static const int ROWS = 22;
    static const int COLS = 12;

private:
    Brick grid[ROWS][COLS];
    shared_ptr<Block> currentBlock;
    int currTurn = 0;
    bool isBomb = false;
    int bombTurn = 0;

    bool triggerBomb(int currturn);
public:
    Board();
    void mergeBlock();
    bool canMove(const Block& block) const;
    void clearLine(int row);
    list<int> checkClearedLines();
    bool setNextBlock(shared_ptr<Block> nextBlock, int currTurn);
    void moveBlock(KeyEnum key);
    const Brick(&getGrid(shared_ptr<Block> block) const)[ROWS][COLS];
    shared_ptr<Block> getCurrentBlock() const;
    void rotateBlock();
};
