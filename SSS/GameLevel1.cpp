#include "GameLevel1.h"
#include "Game.h"

void GameLevel1::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("Img/Levels/SF_Level_1.jpg");

	GameState::Enter();
	

}
