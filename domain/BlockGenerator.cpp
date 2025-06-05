// BlockGenerator.cpp
#include "BlockGenerator.h"
#include "Block.h"
#include "Brick.h"
#include "BrickEnum.h"
#include "cmath"
#include <random>

BlockGenerator::BlockGenerator(Stage stage) :
	minBombScore(stage.getMinBombScore()),
	minEnergyCoreTurn(stage.getMinEnergyCoreTurn()),
	lastBombScore(stage.getMinBombScore()),
	lastEnergyCoreTurn(stage.getMinEnergyCoreTurn())
{
	srand(unsigned(time(NULL)));
}

Block* BlockGenerator::getNextBlock(int currScore, int currTurn)
{
	int bombRate, energyRate;

	bombRate = (int) pow(10.0,(double) (currScore - lastBombScore) / minBombScore);
	energyRate = (int) pow(10.0 ,(double) (currTurn - lastEnergyCoreTurn) / minEnergyCoreTurn);

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
		lastBombScore = currScore;
		return new Block(BrickEnum::BombBrick, startR, startC);
	}

	if (rand() % 100 < energyRate) {
		lastEnergyCoreTurn = currTurn;
		return new Block(BrickEnum::EnergyBrick, startR, startC);
	}

	BrickEnum randomType = bricks[rand() % (sizeof(bricks) / sizeof(bricks[0]))];
	return new Block(randomType, startR, startC);
}
