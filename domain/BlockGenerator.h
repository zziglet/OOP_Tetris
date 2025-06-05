// BlockGenerator.h
#pragma once
#include "Stage.h"
#include "Block.h"

class BlockGenerator {
private:
	int lastBombScore;
	int lastEnergyCoreTurn;
	int minBombScore;
	int minEnergyCoreTurn;

public:
	BlockGenerator(Stage stage);
	Block* getNextBlock(int currScore, int currStage);
};