// Brick.h
#pragma once
#include "BrickEnum.h"

using namespace std;

class Brick {
protected:
    BrickEnum brickType;
    bool isExplosive;

public:
    Brick();
    Brick(BrickEnum brickType);
    Brick(BrickEnum brickType, bool isExplosive);
    bool getIsExplosive() const;
    void setIsExplosive(bool set);
    BrickEnum getBrickType() const;
};

