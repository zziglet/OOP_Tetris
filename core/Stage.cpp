// Stage.cpp
#include "Stage.h"

Stage::Stage(int stageNumber, int duration, int speed, int minBombScore, int minEnergyCoreTurn) :
	stageNumber(stageNumber),
	duration(duration),
	speed(speed),
	minBombScore(minBombScore),
	minEnergyCoreTurn(minEnergyCoreTurn)
{
}

int Stage::getStageNumber() const
{
	return this->stageNumber;
}

int Stage::getDuration() const
{
	return this->duration;
}

int Stage::getSpeed() const
{
	return this->speed;
}

int Stage::getMinBombScore() const
{
	return this->minBombScore;
}

int Stage::getMinEnergyCoreTurn() const
{
	return this->minEnergyCoreTurn;
}