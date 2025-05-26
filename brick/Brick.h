// Brick.h
#pragma once
#include <string>
#include "BrickEnum.h"

using namespace std;

class Brick {
protected:
    BrickEnum brickType;
    bool isExplosive;

public:
    Brick(BrickEnum brickType);
    Brick(BrickEnum brickType, bool isExplosive);
    bool getIsExplosive();
    void setIsExplosive(bool set);
    BrickEnum getBrickType();
};

