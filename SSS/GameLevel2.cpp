#include "GameLevel2.h"
#include "Game.h"


void GameLevel2::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("Img/Levels/SF_Level_2.jpg");

	GameState::Enter();


}