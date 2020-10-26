#pragma once

class GameManager
{
private:
	int hitPoints;
	int score;
public:
	GameManager() { hitPoints = 100; score = 0; }
	int GetHP() { return hitPoints; }
	void TakeDamage(int dmg);
	int GetScore() { return score; }
	void SetScore(int nscore);
};

