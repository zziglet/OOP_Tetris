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
	int minEnergyCoreScore;

public:
	Stage(int stageNumber, int currency, int duration, int speed, int successScore, int minBombScore, int minEnergyCoreScore);
	int getStageNumber() const;
	int getCurrency() const;
	int getDuration() const;
	int getSpeed() const;
	int getSuccessScore() const;
	int getMinBombScore() const;
	int getMinEnergyCoreScore() const;
};