// Stage.h
#pragma once

class Stage {
private:
	int stageNumber;
	int currency;
	int duration;
	int speed;
	int successScore;
	int minBombScore;
	int minEnergyCoreTurn;

public:
	Stage(int stageNumber, int currency, int duration, int speed, int successScore, int minBombScore, int minEnergyCoreTurn);
	int getStageNumber() const;
	int getCurrency() const;
	int getDuration() const;
	int getSpeed() const;
	int getSuccessScore() const;
	int getMinBombScore() const;
	int getMinEnergyCoreTurn() const;
};