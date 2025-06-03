// BlockGenerator.cpp
#include "BlockGenerator.h"
#include "Block.h"
#include "Brick.h"
#include "BrickEnum.h"
#include <random>

BlockGenerator::BlockGenerator(Stage stage) :
	minBombScore(stage.getMinBombScore()),
	minEnergyCoreTurn(stage.getMinEnergyCoreTurn())
{
	srand(unsigned(time(NULL)));
}

Block* BlockGenerator::getNextBlock(int currScore, int currTurn) const
{
	int bombRate, energyRate;

	bombRate = 100 * (currScore - minBombScore) / minBombScore;
	energyRate = 100 * (currTurn - minEnergyCoreTurn) / minEnergyCoreTurn;

	BrickEnum bricks[]{ 
		BrickEnum::LBrick, 
		BrickEnum::RectangleBrick,
		BrickEnum::ReverseLBrick,
		BrickEnum::SBrick,
		BrickEnum::StickBrick,
		BrickEnum::TBrick,
		BrickEnum::ZBrick 
	};

	// 기본 위치: 중앙 상단 (r=0, c=4)
	int startR = 0;
	int startC = 4;

	if (rand() % 100 < bombRate) {
		return new Block(BrickEnum::BombBrick, startR, startC);
	}

	if (rand() % 100 < energyRate) {
		return new Block(BrickEnum::EnergyBrick, startR, startC);
	}

	BrickEnum randomType = bricks[rand() % (sizeof(bricks) / sizeof(bricks[0]))];
	return new Block(randomType, startR, startC);
}
