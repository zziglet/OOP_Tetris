#include <iostream>
#include "brick/Brick.h"
#include "brick/BrickEnum.h"
#include "block/Block.h"
#include "Stage.h"
#include "BlockGenerator.h"
#include "Board.h"

using namespace std;

void printBlock(Block block);
void printBoard(Board A);

int main()
{
	cout << "Tetris project compiled successfully!" << endl;

	Block block(BrickEnum::TBrick, 0, 0);

	printBlock(block);
	block.spin();
	printBlock(block);

	cout << "BlockGenerator, Stage Test" << endl;

	Stage stage = Stage(1,1000,1000,5000,6);

	BlockGenerator generator = BlockGenerator(stage);

	for (int i = 0; i < 1000; i++) {
		BrickEnum A = (*generator.getNextBlock(0, 0)).getBrickType();

		if (A == BrickEnum::BombBrick || A == BrickEnum::EmptyBrick || A == BrickEnum::EnergyBrick) {
			cout << "Error is occured during generating block" << endl;
			break;
		}
	}

	for (int i = 0; i < 7; i++) 
		printBlock(*generator.getNextBlock(7500, 9));

	for (int i = 0; i < 7; i++)
		printBlock(*generator.getNextBlock(6000, 7));

	Board A{};
	
	//A.render();
	int currTurn = 0;
	Block* temp = generator.getNextBlock(currTurn, 0);
	A.setNextBlock(temp, 0);

	for (int i = 0; i < 20; i++) {
		A.moveBlock(KeyEnum::Down);
		printBoard(A);
	}

  return 0;
}


void printBoard(Board A) {
	static int cnt = 1;

	cout << "--------" << cnt++ << "--------" << endl;
	A.render();
}

void printBlock(Block block) {
	static int cnt = 1;

	cout << "--------" << cnt++ << "--------" << endl;
	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << (block.getBrick(i, j) != BrickEnum::EmptyBrick ? "бс " : "бр ");
		}

		cout << endl;
	}

}