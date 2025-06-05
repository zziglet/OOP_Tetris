// BlockGenerator.h
#pragma once
#include "Stage.h"
#include "Block.h"

class BlockGenerator {
private:
	int lastBombScore;
	int lastEnergyCoreScore;
	int minBombScore;
	int minEnergyCoreScore;

public:
	BlockGenerator(Stage stage);
	Block* getNextBlock(int currScore);
};