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

Block BlockGenerator::getNextBlock(int currScore, int currTurn) const
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

	//cout << bombRate << "/" << energyRate << endl;
	//int A = rand() % 100;
	if (rand() % 100 < bombRate) {
		//cout << "A : " << A << endl;
		return Block(BrickEnum::BombBrick,0,0);
	}
	//int B = rand() % 100;
	if ( rand() % 100< energyRate) {
		//cout << "B : " << B << endl;
		return Block(BrickEnum::EnergyBrick, 0, 0);
	}

	return Block(bricks[rand() % (sizeof(bricks) / sizeof(bricks[0]))], 0, 0);

}
