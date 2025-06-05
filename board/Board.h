// board.h
#pragma once
#include "Brick.h"
#include "Block.h"
#include "KeyEnum.h"
#include "list"

using namespace std;

class Board {
public:
    static const int ROWS = 22;
    static const int COLS = 12;

private:
    Brick grid[ROWS][COLS];
    Block* currentBlock;
    int currTurn = 0;
    int bombCnt = 0;
    //대충 폭탄이 있다는 뜻.
    bool isBomb = false;
    //폭탄이 언제 생겼는지 저장하는 변수.
    int bombTurn = 0;

    void triggerEnergyCore(int startRow, int endRow);
    bool triggerBomb(int currturn);

public:
    Board();

    void mergeBlock();
    bool canMove(const Block& block) const;
    void clearLines(list<int> clearLines);
    list<int> checkClearedLines();
    bool setNextBlock(Block* nextBlock, int currTurn);
    void moveBlock(KeyEnum key);
    const Brick(&getGrid(Block* block) const)[ROWS][COLS];
    void render();

    Block* getCurrentBlock() const;
    void rotateBlock(); // 회전 시도 함수
};
