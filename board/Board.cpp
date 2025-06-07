// board.cpp
#pragma once
#include "Board.h"
#include <iostream>
#include "Block.h"
#include "Brick.h"
#include "KeyEnum.h"
#include "vector"
#include "algorithm"
#include "random"
#include "list"
#include "Renderer.h"

using namespace std;

Board::Board() {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }

    currentBlock = nullptr;
}

void Board::clearLines(list<int> clearLines)
{
    int return_val = clearLines.size();
    clearLines.sort();


    while (clearLines.size() != 0) {
        int now = clearLines.front();
        clearLines.pop_front();
        bool isCheck = false;

        for (int j = 0; j < COLS; j++) {
            if (grid[now][j].getBrickType() == BrickEnum::BombBrick) {
                isBomb = false;
            }
            /*if (grid[now][j].getBrickType() == BrickEnum::EmptyBrick) {
                isCheck = true;
            }*/
        }

        /* 혹시 지워야하는 라인에 빈 블록이 있다면 continue
        if (isCheck)
            continue;*/

        for (int k = now; k > 0; k--) {
            for (int j = 0; j < COLS; j++) {
                grid[k][j] = grid[k - 1][j];
            }
        }

    }
}

void Board::clearLine(int row)
{
    for (int j = 0; j < COLS; j++) {
        if (grid[row][j].getBrickType() == BrickEnum::BombBrick) {
            isBomb = false;
        }
    }
    
    for (int k = row; k > 0; k--) {
        for (int j = 0; j < COLS; j++) {
            grid[k][j] = grid[k - 1][j];
        }
    }


}


list<int> Board::checkClearedLines() {

    list<int> clearLines;

    for (int i = 0; i < ROWS; i++) {

        bool full = true;

        for (int j = 0; j < COLS; j++) {
            if (grid[i][j].getBrickType() == BrickEnum::EmptyBrick) {
                full = false;
                break;
            }
        }

        if (full) {
            for (int j = 0; j < COLS; j++) {

                if (grid[i][j].getBrickType() == BrickEnum::EnergyBrick) {
                    if (0 <= i + 1 && i + 1 < ROWS)
                        clearLines.push_back(i + 1);
                    if (0 <= i - 1 && i - 1 < ROWS)
                        clearLines.push_back(i - 1);
                }
            }

            clearLines.push_back(i);


        }

    }

    if (clearLines.size() != 0) {
        clearLines.sort();
        clearLines.unique();
    }


    return clearLines;
    /*int return_val = clearLines.size();

    while (clearLines.size() != 0) {
        int now = clearLines.back();

        for (int k = now; k > 0; k--) {
            for (int j = 0; j < COLS; j++) {
                grid[k][j] = grid[k - 1][j];
            }
        }

        clearLines.pop_back();
    }*/


    //return return_val;
}

bool Board::setNextBlock(shared_ptr<Block> nextBlock, int currTurn) {

    currentBlock = nextBlock;
    this->currTurn = currTurn;

    bool bombTriggered = triggerBomb(currTurn);

    //cout << "spinCnt : " <<  currentBlock->getSpinCnt() << endl;

    if (currentBlock->getBrickType() == BrickEnum::BombBrick) {
        isBomb = true;
        bombTurn = currTurn;

        vector<pair<int, int>> temp;

        for (int i = 4; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {

                BrickEnum now = grid[i][j].getBrickType();

                if (now == BrickEnum::WallBrick || now == BrickEnum::EmptyBrick)
                    continue;

                temp.push_back({ i,j });
            }
        }

        

        std::random_device rd;
        std::mt19937 g(rd());

        shuffle(temp.begin(), temp.end(), g);
        int cnt = 0;

        while (cnt < (temp.size() < 3 ? temp.size() : 3)){
            //std::cout << cnt << " : " << temp.size() << std::endl;
            pair<int, int> A = temp.at(cnt++);
            //std::cout << "A : " << A.first << " : " << A.second << " : " << temp.size() << std::endl;
            //std::cout << cnt << (temp.size() < 3 ? temp.size() : 3) << std::endl;
            grid[A.first][A.second].setIsExplosive(true);
        }

    }

    return bombTriggered;
}

void Board::moveBlock(KeyEnum key) {
    if (currentBlock == nullptr)
        return;

    Block moved = *currentBlock;

    switch (key) {
    case KeyEnum::Left:
        moved.c -= 1;
        break;
    case KeyEnum::Right:
        moved.c += 1;
        break;
    case KeyEnum::Down:
        moved.r += 1;
        break;
    default:
        return;
    }

    if (canMove(moved)) {
        currentBlock->r = moved.r;
        currentBlock->c = moved.c;
    }
    else if (key == KeyEnum::Down) {
        mergeBlock();
    }
}


const Brick(&Board::getGrid(shared_ptr<Block> block) const)[ROWS][COLS]{
    static Brick return_grid[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            return_grid[i][j] = grid[i][j];
        }
    }

    if (block != nullptr) {
        int spin = block->getSpinCnt();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block->shape[spin][i][j] != BrickEnum::EmptyBrick) {
                    int r = block->r + i;
                    int c = block->c + j;

                    if (0 <= r && r < ROWS && 0 <= c && c < COLS) {
                        return_grid[r][c] = Brick(block->shape[spin][i][j]);
                    }
                }
            }
        }
    }

    return return_grid;
}

bool Board::canMove(const Block& block) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block.shape[block.getSpinCnt()][i][j] != BrickEnum::EmptyBrick) {
                int newR = block.r + i;
                int newC = block.c + j;

                if (newR < 0 || newR >= ROWS || newC < 0 || newC >= COLS)
                    return false;
                if (grid[newR][newC].getBrickType() != BrickEnum::EmptyBrick)
                    return false;
            }
        }
    }
    return true;
}


void Board::mergeBlock() {
    if (!currentBlock) return;

    int baseR = currentBlock->r;
    int baseC = currentBlock->c;

    BrickEnum type = currentBlock->getBrickType();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentBlock->shape[currentBlock->getSpinCnt()][i][j] != BrickEnum::EmptyBrick) {
                int r = baseR + i;
                int c = baseC + j;

                if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                    grid[r][c] = Brick(type);
                }
            }
        }
    }

    //checkClearedLines();
    currentBlock = nullptr;
}

void Board::triggerEnergyCore(int startRow, int endRow) {

    for (int i = startRow; i <= endRow; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }

}

bool Board::triggerBomb(int currTurn) {
    bool bombHappened = false;

    list<pair<int, int>> bombList;

    if (currTurn - bombTurn == 4) {
        if (isBomb) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {

                    if (grid[i][j].getIsExplosive()) {
                        bombList.push_back({ i,j });
                        bombCnt++;
                        bombHappened = true;
                    }

                }
            }
            isBomb = false;
        }
    }

    if (bombHappened) {
        Renderer::drawBomb(*this, bombList);
        
        /*for (auto i : bombList) {
            std::cout << i.first << " " << i.second << " / ";
        }*/
    }

    for (auto i : bombList) {
        grid[i.first][i.second] = Brick();
    }

    return bombHappened;
}

void Board::render() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << (grid[i][j].getBrickType() == BrickEnum::EmptyBrick ? 0 : 1) << " ";
        }
        std::cout << std::endl;
    }
}

shared_ptr<Block> Board::getCurrentBlock() const {
    /*if (!currentBlock) {
        std::cout << "[DEBUG] getCurrentBlock(): currentBlock is nullptr\n";
    }*/
    return currentBlock;
}

void Board::rotateBlock() {
    /*if (!currentBlock) {
        std::cout << "[DEBUG] rotateBlock 실패: currentBlock이 nullptr입니다.\n";
        return;
    }*/

    int nextSpin = (currentBlock->getSpinCnt() + 1) % 4;

    Block rotated = *currentBlock;
    rotated.setSpinCnt(nextSpin);

    if (canMove(rotated)) {
        currentBlock->spin();
    }
    else {
        std::cout << "[DEBUG] rotateBlock 실패: 회전 불가능한 위치입니다. "
            << "r=" << rotated.r << ", c=" << rotated.c << ", nextSpin=" << nextSpin << "\n";
    }
}
