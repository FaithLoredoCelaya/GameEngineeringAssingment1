#include "GameLevel3.h" 
#include "Game.h"

void GameLevel3::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("Img/Levels/SF_Level_3.jpg");

	GameState::Enter();


}
