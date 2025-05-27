// Block.h
#pragma once
#include "../brick/Brick.h"
#include "../brick/BrickEnum.h"
#include <memory>
#include <iostream>

class Block {
public:
    int r, c;

protected:
    BrickEnum brickType;
    char shape[4][4][4];
    int spinCnt = 0;

public:
    Block(BrickEnum brickType, int r, int c);
    BrickEnum getBrick(int r, int c);
    BrickEnum getBrickType();
    void spin();
};