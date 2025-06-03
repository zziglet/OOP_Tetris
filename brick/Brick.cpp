#include "Brick.h"

Brick::Brick() : brickType(BrickEnum::EmptyBrick), isExplosive(false) {
}

Brick::Brick(BrickEnum brickType) : Brick(brickType, false)
{
}

Brick::Brick(BrickEnum brickType, bool isExplosive) : 
    brickType(brickType),
    isExplosive(isExplosive)
{
}

bool Brick::getIsExplosive()
{
    return this->isExplosive;
}

void Brick::setIsExplosive(bool set)
{
    this->isExplosive = set;
}

BrickEnum Brick::getBrickType() const
{
    return this->brickType;
}
