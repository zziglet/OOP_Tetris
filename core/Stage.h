// Stage.h
#pragma once

class Stage {
private:
	int stageNumber;
	int duration;
	int speed;
	int minBombScore;
	int minEnergyCoreTurn;

public:
	Stage(int stageNumber, int duration, int speed, int minBombScore, int minEnergyCoreTurn);
	int getStageNumber() const;
	int getDuration() const;
	int getSpeed() const;
	int getMinBombScore() const;
	int getMinEnergyCoreTurn() const;
};