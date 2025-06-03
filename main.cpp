#include "GameManager.h"

int main() {
    GameManager gameManager;
    gameManager.startGame();
    return 0;
}

//int main() {
//    Stage stage(1, 1000, 1000, 5000, 6);
//    BlockGenerator generator(stage);
//    Board board;
//
//    Block* block = generator.getNextBlock(0, 0);
//    block->r = 5; block->c = 5; // 중간쯤 위치시키기
//    board.setNextBlock(block, 0);
//
//    Renderer renderer;
//    renderer.drawBoard(board); // 블럭 보이는지 확인
//
//    return 0;
//}

