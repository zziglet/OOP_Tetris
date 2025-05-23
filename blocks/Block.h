// Block.h
#pragma once
#include "Brick.h"
#include "BrickEnum.h"
#include <memory>

class Block{
public:
    int r,c;

protected:
    BrickEnum brickType;
    char shape[4][4][4];
    int spinCnt = 0;
    
public:
    Block(BrickEnum brickType,int r, int c);
    BrickEnum getBrick(int r, int c);
    void spin();
    

};
