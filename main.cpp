#include <iostream>
#include "brick/Brick.h"
#include "brick/BrickEnum.h"
#include "blocks/base/Block.h"

using namespace std;

int main()
{
  cout << "Tetris project compiled successfully!" << endl;

  Block block(BrickEnum::TBrick, 0, 0);

  for (int i = 0; i < 4; i++) {
	  for (int j = 0; j < 4; j++) {
		  cout << (block.getBrick(i, j) != BrickEnum::EmptyBrick ? "бс " : "бр ");
	  }

	  cout << endl;
  }

  block.spin();

  for (int i = 0; i < 4; i++) {
	  for (int j = 0; j < 4; j++) {
		  cout << (block.getBrick(i, j) != BrickEnum::EmptyBrick ? "бс " : "бр ");
	  }

	  cout << endl;
  }

  return 0;
}
