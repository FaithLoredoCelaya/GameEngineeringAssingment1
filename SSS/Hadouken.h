#pragma once
#include "SpriteEx.h"

class Hadouken : public SpriteExAnimated
{
public:
	friend class Player;
	Hadouken(SDL_Texture* tex, double x, double y, double a, double dx, double dy)
		:
		SpriteExAnimated(tex, x, y, a)
	{
		m_DX = dx;
		m_DY = dy;
		spriteSrcRect = { 100,0,24,24 };
		spriteDestRect = { (int)(x - 12),(int)(y - 12),24,24 };
		m_dRadius = 8;
	}


	void Update()
	{
		m_X += (m_DX * m_dSpeed);
		m_Y += (m_DY * m_dSpeed);

		this->UpdateDestRect();
	}
	

};
