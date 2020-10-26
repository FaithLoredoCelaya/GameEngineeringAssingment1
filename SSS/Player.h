#pragma once
#include "SpriteEx.h"
#include <vector>
#include <functional>
using namespace std;
class Player : public SpriteExAnimated
{
private:
	double m_velX = 0,
		m_velY = 0,
		preJumpYVal=0,
		m_velMax = 10;
	void MovePlayer(bool isFwd);
	void UpdatePlayer();
public:
	Player();
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	virtual void Update();
	//virtual void TakeDamage();
	virtual void Render();
	//void SetIdle();
	virtual void Jump();
	void OnJumpAnimComplete();

};