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


// List∑Œ µÈæÓø¬ ∂Û¿Œ ¡¶∞≈.
void Board::clearLines(list<int> clearLines)
{
    //« ø‰«“ ºˆµµ? ¿÷æÓº≠ ¿œ¥‹ ¿˚æÓµ“
    int return_val = clearLines.size();
    //¿ßø° ¡Ÿ∫Œ≈Õ ¡¶∞≈«ÿæﬂ«œπ«∑Œ sort()
    clearLines.sort();


    while (clearLines.size() != 0) {
        int now = clearLines.front();
        clearLines.pop_front();
        bool isCheck = false;

        // ∆¯≈∫ ¡¶∞≈µ«¥¬ ∞ÊøÏ, isBomb∏¶ false∑Œ ∫Ø∞Ê
        for (int j = 0; j < COLS; j++) {
            if (grid[now][j].getBrickType() == BrickEnum::BombBrick) {
                isBomb = false;
            }
            if (grid[now][j].getBrickType() == BrickEnum::EmptyBrick) {
                isCheck = true;
            }
        }

        // »§Ω√ ¡ˆøˆæﬂ«œ¥¬ ∂Û¿Œø° ∫Û ∫Ì∑œ¿Ã ¿÷¥Ÿ∏È continue
        if (isCheck)
            continue;


        //∂Û¿Œ ¡¶∞≈«œ∞Ì ¿ßø° ∫Ì∑œ ≥ª∏Æ¥¬ ¿€æ˜ Ω√«‡.
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

<<<<<<< HEAD
            
=======
            // ??ÉÑ ?úÍ±∞?òÎäî Í≤ΩÏö∞, isBombÎ•?falseÎ°?Î≥ÄÍ≤?
>>>>>>> 097b148f9f32835cc6457c8574c87beaaad73bf7
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

bool Board::isGameOver() {

    if (bombCnt >= 3) {
        return true;
    }

    const int VISIBLE_START_ROW = 4;

    for (int i = 0; i < VISIBLE_START_ROW; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j].getBrickType() != BrickEnum::EmptyBrick) {
                return true;
            }
        }
    }

    return false;
}

void Board::setNextBlock(Block* nextBlock, int currTurn) {


    //∞‘¿”∏ﬁ¥œ¡Æ∞° ∏±∏Æ¡Ó æ»«“∞≈∏È æ∆∑° ¡÷ºÆ ¡¶∞≈ «ÿæﬂ«‘.
    //delete currentBlock;

    currentBlock = nextBlock;
    this->currTurn = currTurn;

    
    triggerBomb(currTurn);

    //cout << "spinCnt : " <<  currentBlock->getSpinCnt() << endl;

    if (currentBlock->getBrickType() == BrickEnum::BombBrick) {
        //?úÎç§?ºÎ°ú Î∏îÎ°ù???†ÌÉù?¥ÏÑú, Í∑∏Í≤å ??ÉÑ?ºÎ°ú ?∞Ï?Í≤??¥Ïïº??
        isBomb = true;
        bombTurn = currTurn;

        vector<pair<int, int>> temp;
        //≈Õ¡˙ ∫Ì∑œ »ƒ∫∏ º±≈√
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
        // »ƒ∫∏µÈ º≈«√«‘.
        shuffle(temp.begin(), temp.end(), g);

<<<<<<< HEAD

        // √÷¥Î 3∞≥±Ó¡ˆ ≈Õ¡ˆπ«∑Œ æ∆∑° while∑Œ º±≈√.
=======
>>>>>>> 097b148f9f32835cc6457c8574c87beaaad73bf7
        while (cnt < temp.size() || cnt == 3) {
            pair<int, int> A = temp.at(cnt++);
            grid[A.first][A.second].setIsExplosive(true);
        }

    }

}



void Board::moveBlock(KeyEnum key) {
    if (currentBlock == nullptr) 
        return;

    int dr = 0, dc = 0;

    // Î∞©Ìñ• Í≤∞Ï†ï
    switch (key) {
    case KeyEnum::Left:  dc = -1; break;
    case KeyEnum::Right: dc = 1; break;
    case KeyEnum::Down:  dr = 1; break;
    default: return;
    }

    int newR = currentBlock->r + dr;
    int newC = currentBlock->c + dc;

    // ?¥Îèô Í∞Ä???¨Î? ?ïÏù∏
    if (canMove(newR, newC, currentBlock->getSpinCnt())) {
        currentBlock->r = newR;
        currentBlock->c = newC;
        //cout << currentBlock->r << " : " << currentBlock->c << endl;
    }
    // ¿Ã ∫Œ∫– ¡§ªÛ¿€µø «“∑√¡ˆ ∏∏£∞⁄¿Ω tc«ÿæﬂ«“µÌ
    else if (key == KeyEnum::Down) {
<<<<<<< HEAD
        // æ∆∑°∑Œ ¿Ãµø ∫“∞°¥…«œ∏È ∞Ì¡§
=======
        // ?ÑÎûòÎ°??¥Îèô Î∂àÍ??•ÌïòÎ©?Í≥†Ï†ï
        //cout << "asdfasdfasdfasdfasdfasdfasdfadsf" << endl;
>>>>>>> 097b148f9f32835cc6457c8574c87beaaad73bf7
        mergeBlock();
    }

}

bool Board::canMove(int r, int c, int spin) {

    if (currentBlock == nullptr) {
        return false;
    }


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {   
            //cout << i << " : " << j << spin << endl;
            if (currentBlock->shape[spin][i][j] != BrickEnum::EmptyBrick) {

                int newR = r + i;
                int newC = c + j;

                // Î≤îÏúÑ Ï≤¥ÌÅ¨
                if (newR < 0 || newR >= ROWS || newC < 0 || newC >= COLS)
                    return false;

                // ?¥Î? Ï±ÑÏõåÏß?Î∏îÎü≠???àÎäî Í≤ΩÏö∞
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

void Board::triggerBomb(int currTurn) {
    
    if (currTurn - bombTurn == 4) {
        if (isBomb) {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    
                    if (grid[i][j].getIsExplosive()) {
                        grid[i][j] = Brick();
                        bombCnt++;
                    }
                
                }
            }
            isBomb = false;
        }
       
    }
}

//µπˆ±◊øÎ
void Board::render() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << (grid[i][j].getBrickType() == BrickEnum::EmptyBrick ? 0 : 1) << " ";
        }
        std::cout << std::endl;
    }
}
