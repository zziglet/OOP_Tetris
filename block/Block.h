// Block.h
#pragma once
#include "../brick/Brick.h"
#include "../brick/BrickEnum.h"
#include <memory>
#include <iostream>

class Block {
public:
    int r, c;
    BrickEnum brickType;
    BrickEnum shape[4][4][4];

private:
    int spinCnt;

public:
    Block(BrickEnum brickType, int r, int c);
    BrickEnum getBrick(int r, int c);
    BrickEnum getBrickType();
    
    int getSpinCnt() const;
    void spin();
    void setSpinCnt(int value) { spinCnt = value; }
};