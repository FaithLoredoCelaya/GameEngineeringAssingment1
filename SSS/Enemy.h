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
	int randMove;
	string attack;
	
	unsigned int lastTime = 0, currentTime;

public:
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	void Update() override;
	void Render();
	void Attack();
	void Defend();
	void Move();
	void SetCanAttack(bool atk) { canAttack = atk; }
};