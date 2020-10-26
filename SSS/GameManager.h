#pragma once

class GameManager
{
private:
	int hp = 100;
	int score = 0;

public:
	GameManager() { }
	int GetHP() { return hp; }
	void TakeDamage(int dmg) { hp -= dmg; };
	int GetScore() { return score; }
	void SetScore(int nscore) { score += nscore; };
};

