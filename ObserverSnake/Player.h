#pragma once
#include <iostream>
#include"Console.h"
class Player {
private:
	unsigned int currentScore;	//arr use to save current score of 4 maps
	unsigned int totalScore;		//arr use to save total score of each map

	// required
	int _skillUIMarginLeft;

public:
	Player(int skillUIMarginLeft);
	void resetScore();
	void addScore(int score = 10);
	unsigned int getCurrentScore();
	unsigned int getTotalScore();
	void saveScore();
	void showCurrentScore();

	int getSkillUIMarginLeft() { return _skillUIMarginLeft; };
};

