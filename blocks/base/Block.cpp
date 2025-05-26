// Block.cpp
#include "Block.h"

Block::Block(BrickEnum brickType, int r, int c) :
    brickType(brickType), r(r), c(c)
{

    if (brickType == BrickEnum::BombBrick) {

        char temp[4][4][4] = {
            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];

    }

    else if (brickType == BrickEnum::EnergyBrick) {

        char temp[4][4][4] = {
            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,1,0,0,
            0,0,0,0,
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];

    }

    else if (brickType == BrickEnum::ReverseLBrick) {
        char temp[4][4][4] = {
            1,1,0,0,
            1,0,0,0,
            1,0,0,0,
            0,0,0,0,

            1,0,0,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0,

            0,1,0,0,
            0,1,0,0,
            1,1,0,0,
            0,0,0,0,

            1,1,1,0,
            0,0,1,0,
            0,0,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];
    }

    else if (brickType == BrickEnum::LBrick) {

        char temp[4][4][4] = {
            1,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,0,0,0,

            1,1,1,0,
            1,0,0,0,
            0,0,0,0,
            0,0,0,0,


            1,0,0,0,
            1,0,0,0,
            1,1,0,0,
            0,0,0,0,

            0,0,1,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];

    }

    else if (brickType == BrickEnum::RectangleBrick) {
        char temp[4][4][4] = {
            1,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,1,0,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];
    }

    else if (brickType == BrickEnum::SBrick) {
        char temp[4][4][4] = {
            0,1,1,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,0,0,0,
            1,1,0,0,
            0,1,0,0,
            0,0,0,0,

            0,1,1,0,
            1,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,0,0,0,
            1,1,0,0,
            0,1,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];
    }

    else if (brickType == BrickEnum::TBrick) {
        char temp[4][4][4] = {
            0,1,0,0,
            1,1,0,0,
            0,1,0,0,
            0,0,0,0,

            1,1,1,0,
            0,1,0,0,
            0,0,0,0,
            0,0,0,0,

            1,0,0,0,
            1,1,0,0,
            1,0,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,1,0,
            0,0,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];
    }

    else if (brickType == BrickEnum::StickBrick) {
        char temp[4][4][4] = {
            1,0,0,0,
            1,0,0,0,
            1,0,0,0,
            1,0,0,0,

            1,1,1,1,
            0,0,0,0,
            0,0,0,0,
            0,0,0,0,

            1,0,0,0,
            1,0,0,0,
            1,0,0,0,
            1,0,0,0,

            1,1,1,1,
            0,0,0,0,
            0,0,0,0,
            0,0,0,0,
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];

    }

    else if (brickType == BrickEnum::ZBrick) {
        char temp[4][4][4] = {
            1,1,0,0,
            0,1,1,0,
            0,0,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,0,0,
            1,0,0,0,
            0,0,0,0,

            1,1,0,0,
            0,1,1,0,
            0,0,0,0,
            0,0,0,0,

            0,1,0,0,
            1,1,0,0,
            1,0,0,0,
            0,0,0,0
        };

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    shape[i][j][k] = temp[i][j][k];

    }

    else {
        std::cout << "Error is occured during making a Block" << std::endl;
    }
}

BrickEnum Block::getBrick(int r, int c)
{
    return this->shape[spinCnt][r][c] ? this->brickType : BrickEnum::EmptyBrick;
}

void Block::spin()
{
    this->spinCnt = (this->spinCnt + 1) % 4;

}
