// BlockGenerator.h
#pragma once
#include "Stage.h"
#include "Block.h"

#include <memory>

class BlockGenerator {
private:
	int lastBombScore;
	int lastEnergyCoreScore;
	int minBombScore;
	int minEnergyCoreScore;
	int lastBombTurn;
public:
	BlockGenerator(Stage stage);
	shared_ptr<Block> getNextBlock(int currScore,int currTurn);
};