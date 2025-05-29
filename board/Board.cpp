// board.cpp
#include "Board.h"
#include <iostream>
#include "Block.h"
#include "Brick.h"
#include "KeyEnum.h"

Board::Board() {
    // Initialize all cells to EmptyBrick
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }
    currentBlock = nullptr; //  GameManager�� �ص� �Ǵ� �κ�
}

int Board::clearFullLines() {
    int cleared = 0;
    for (int i = 0; i < ROWS; ++i) {
        bool full = true;
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j].getBrickType() == BrickEnum::EmptyBrick) {
                full = false;
                break;
            }
        }
        if (full) {
            ++cleared;
            // ��� ���� �ϳ��� ������
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < COLS; ++j) {
                    grid[k][j] = grid[k - 1][j];
                }
            }
            // ���� ����
            for (int j = 0; j < COLS; ++j) {
                grid[0][j] = Brick(BrickEnum::EmptyBrick);
            }
        }
    }
    return cleared;
}

bool Board::isGameOver() {
    for (int j = 0; j < COLS; ++j) {
        if (grid[0][j].getBrickType() != BrickEnum::EmptyBrick) {
            return true;
        }
    }
    return false;
}

void Board::moveBlock(KeyEnum key) {
    if (!currentBlock) return;

    int dr = 0, dc = 0;

    // ���� ����
    switch (key) {
    case KeyEnum::Left:  dc = -1; break;
    case KeyEnum::Right: dc = 1; break;
    case KeyEnum::Down:  dr = 1; break;
    default: return;
    }

    int newR = currentBlock->r + dr;
    int newC = currentBlock->c + dc;

    // �̵� ���� ���� Ȯ��
    if (canMove(newR, newC, currentBlock->getSpinCnt())) {
        currentBlock->r = newR;
        currentBlock->c = newC;
    }
    else if (key == KeyEnum::Down) {
        // �Ʒ��� �̵� �Ұ����ϸ� ����
        mergeBlock();
    }
}

bool Board::canMove(int r, int c, int spin) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentBlock->getShape()[spin][i][j] == '#') {
                int newR = r + i;
                int newC = c + j;
                // ���� üũ
                if (newR < 0 || newR >= ROWS || newC < 0 || newC >= COLS)
                    return false;
                // �̹� ä���� ���� �ִ� ���
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

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentBlock->getShape()[currentBlock->getSpinCnt()][i][j] == '#') {
                int r = baseR + i;
                int c = baseC + j;

                if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                    grid[r][c] = Brick(type);
                }
            }
        }
    }

    // Ư�� ��� ��� ����
    if (type == BrickEnum::BombBrick) {
        triggerBomb();
    }
    else if (type == BrickEnum::EnergyBrick) {
        // �� ���ÿ����� ����� ������ �� ������ ���� trigger
        triggerEnergyCore(baseR, baseR + 3);
    }

    clearFullLines();
    currentBlock = nullptr;
}

void Board::triggerEnergyCore(int startRow, int endRow) {
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = Brick(BrickEnum::EmptyBrick);
        }
    }
}

void Board::triggerBomb() {
    //���߿� GameManager ���� ��, �ۼ� ����
}

void Board::render() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << static_cast<int>(grid[i][j].getBrickType()) << " ";
        }
        std::cout << std::endl;
    }
}
