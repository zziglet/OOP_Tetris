// BlockGenerator.cpp
#include "BlockGenerator.h"
#include "Block.h"
#include "Brick.h"
#include "BrickEnum.h"
#include "cmath"
#include "iostream"
#include "Renderer.h"

#include <random>
#include <memory>


BlockGenerator::BlockGenerator(Stage stage) :
	minBombScore(stage.getMinBombScore()),
	minEnergyCoreScore(stage.getMinEnergyCoreScore()),
	lastBombScore(stage.getMinBombScore()),
	lastEnergyCoreScore(stage.getMinEnergyCoreScore())
{
	srand(unsigned(time(NULL)));
}

shared_ptr<Block> BlockGenerator::getNextBlock(int currScore)
{
	int bombRate, energyRate;

	bombRate = (int) pow(10.0,(double) (currScore - lastBombScore) / minBombScore);
	energyRate = (int) pow(10.0 ,(double) (currScore - lastEnergyCoreScore) / minEnergyCoreScore);
	
	//Renderer::gotoXY(500, 500);
	//std::cout << bombRate << " : " << energyRate << std::endl;

	
	BrickEnum bricks[]{ 
		BrickEnum::LBrick, 
		BrickEnum::RectangleBrick,
		BrickEnum::ReverseLBrick,
		BrickEnum::SBrick,
		BrickEnum::StickBrick,
		BrickEnum::TBrick,
		BrickEnum::ZBrick 
	};

	int startR = 0;
	int startC = 4;

	if (rand() % 100 < energyRate) {
		lastEnergyCoreScore = currScore;
		return make_shared<Block>(BrickEnum::EnergyBrick, startR, startC);
	}

	if (rand() % 100 < bombRate) {
		lastBombScore = currScore;
		return make_shared<Block>(BrickEnum::BombBrick, startR, startC);
	}

	BrickEnum randomType = bricks[rand() % (sizeof(bricks) / sizeof(bricks[0]))];
	return make_shared<Block>(randomType, startR, startC);
}
