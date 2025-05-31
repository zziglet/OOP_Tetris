// BlockGenerator.h
#pragma once
#include "Stage.h"
#include "Block.h"

class BlockGenerator {
private:
	int lastBombScore = 0;
	int lastEnergyCoreTurn = 0;
	int minBombScore;
	int minEnergyCoreTurn;

public:
	BlockGenerator(Stage stage);
	Block* getNextBlock(int currScore, int currStage) const;
};