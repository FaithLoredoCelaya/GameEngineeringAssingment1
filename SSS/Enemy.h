#pragma once
#include "Player.h"
#include "GameManager.h"

class Enemy : public Player
{
private:
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;

	void UpdateEnemy();
	int randDefNum;
	int randAttackNum;
	bool isAtPlayer;
	int randMove;
	unsigned int lastTime = 0, currentTime;
	GameManager health;
	int dmgToReceive = 0;

	int attackType=0;

public:
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	int GetAttack() { return attackType; }
	void Update() override;
	void Render();
	void Attack();
	void ReRoll();
	int GetRng();
	void Move();
	void Defend();
	void TakeHit();
};