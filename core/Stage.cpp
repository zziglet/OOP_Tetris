// Stage.cpp
#include "Stage.h"

Stage::Stage(int stageNumber, int currency, int duration, int speed, int successScore, int minBombScore, int minEnergyCoreTurn) :
	stageNumber(stageNumber),
	currency(currency),
	duration(duration),
	speed(speed),
	successScore(successScore),
	minBombScore(minBombScore),
	minEnergyCoreTurn(minEnergyCoreTurn)
{
}

int Stage::getStageNumber() const
{
	return this->stageNumber;
}

int Stage::getCurrency() const
{
	return this->currency;
}

int Stage::getDuration() const
{
	return this->duration;
}

int Stage::getSpeed() const
{
	return this->speed;
}

int Stage::getSuccessScore() const
{
	return this->successScore;
}

int Stage::getMinBombScore() const
{
	return this->minBombScore;
}

int Stage::getMinEnergyCoreTurn() const
{
	return this->minEnergyCoreTurn;
}