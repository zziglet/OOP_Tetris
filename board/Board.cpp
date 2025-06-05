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

using namespace std;


Board::Board() {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }

    currentBlock = nullptr;
}


// List로 들어온 라인 제거.
void Board::clearLines(list<int> clearLines)
{
    //필요할 수도? 있어서 일단 적어둠
    int return_val = clearLines.size();
    //위에 줄부터 제거해야하므로 sort()
    clearLines.sort();


    while (clearLines.size() != 0) {
        int now = clearLines.front();
        clearLines.pop_front();
        bool isCheck = false;

        // 폭탄 제거되는 경우, isBomb를 false로 변경
        for (int j = 0; j < COLS; j++) {
            if (grid[now][j].getBrickType() == BrickEnum::BombBrick) {
                isBomb = false;
            }
            /*if (grid[now][j].getBrickType() == BrickEnum::EmptyBrick) {
                isCheck = true;
            }*/
        }


        // 에너지 코어 블록이 지우는 라인은 빈 블록이 있으므로 체크 X

        /* 혹시 지워야하는 라인에 빈 블록이 있다면 continue
        if (isCheck)
            continue;*/


        //라인 제거하고 위에 블록 내리는 작업 시행.
        for (int k = now; k > 0; k--) {
            for (int j = 0; j < COLS; j++) {
                grid[k][j] = grid[k - 1][j];
            }
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
                    if(0<= i + 1 && i+1 < ROWS)
                        clearLines.push_back(i + 1);
                    if (0 <= i - 1 && i - 1 < ROWS)
                        clearLines.push_back(i - 1);
                }
            }

            clearLines.push_back(i);
            

        }

    }

    clearLines.sort();
    clearLines.unique();
    
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

bool Board::setNextBlock(Block* nextBlock, int currTurn) {


    //게임메니져가 릴리즈 안할거면 아래 주석 제거 해야함.
    //delete currentBlock;

    currentBlock = nextBlock;
    this->currTurn = currTurn;
    
    bool bombTriggered = triggerBomb(currTurn);  // 폭탄 터졌는지 확인

    //cout << "spinCnt : " <<  currentBlock->getSpinCnt() << endl;

    if (currentBlock->getBrickType() == BrickEnum::BombBrick) {
        isBomb = true;
        bombTurn = currTurn;

        vector<pair<int, int>> temp;
        //터질 블록 후보 선택
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {

                BrickEnum now = grid[i][j].getBrickType();
                
                if (now == BrickEnum::WallBrick || now == BrickEnum::EmptyBrick) 
                    continue;
                
                temp.push_back({ i,j });
            }
        }

        int cnt = 0;

        std::random_device rd;
        std::mt19937 g(rd());
        // 후보들 셔플함.
        shuffle(temp.begin(), temp.end(), g);


        // 최대 3개까지 터지므로 아래 while로 선택.
        while (cnt < temp.size() || cnt == 3) {
            pair<int, int> A = temp.at(cnt++);
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
        mergeBlock();  // 더 이상 아래로 못 내려가면 고정
    }
}


const Brick(&Board::getGrid(Block* block) const)[ROWS][COLS]{
    static Brick return_grid[ROWS][COLS];  // static으로 유지

    // 원래 grid 복사
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            return_grid[i][j] = grid[i][j];
        }
    }

    // 전달된 block 덧씌우기
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

    if (currTurn - bombTurn == 4) {
        if (isBomb) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    
                    if (grid[i][j].getIsExplosive()) {
                        grid[i][j] = Brick();
                        bombCnt++;
                        bombHappened = true;
                    }
                
                }
            }
            isBomb = false;
        }
       
    }
    return bombHappened;
}

//디버그용
void Board::render() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << (grid[i][j].getBrickType() == BrickEnum::EmptyBrick ? 0 : 1) << " ";
        }
        std::cout << std::endl;
    }
}

Block* Board::getCurrentBlock() const {
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

    // 회전한 블록을 복사하여 검사
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
