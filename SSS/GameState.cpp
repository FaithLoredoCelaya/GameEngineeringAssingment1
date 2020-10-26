#include "GameState.h"
#include "Game.h"
#include "PauseMenuPopupState.h"

void GameState::Enter()
{
	mainSpriteTex = Game::Instance()->LoadTexture("Img/Players/PlayerKenSprite2.png");
	EnemySpriteTex = Game::Instance()->LoadTexture("Img/Players/EnemySprite.png");

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 30);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	gm = new GameManager();
	  
	player = new Player(mainSpriteTex, bgDestRect.w*0.5, bgDestRect.h - 100);

	enemy = new Enemy(EnemySpriteTex, bgDestRect.w * 0.7, bgDestRect.h - 100);
 
}


void GameState::Update()
{
	if (Game::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		Game::Instance()->GetFSM()->PushState(new PauseMenuPopupState());
		return; //to make sure we don't run the game in background while pause menu shows
	}

	if (player) player->Update();

	if (enemy) enemy->Update();
 

	if (player) this->CheckCollision();
	if (enemy) this->CheckAttackRange();

 
}


void GameState::Render()
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(Game::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) player->Render();
	if (enemy) enemy->Render();

	ScreenState::Render();

}


void GameState::Exit()
{
	//to-do:: de-allocate memory, texture, surface etc, sound 
	//player->~Player();
	//enemy->~Enemy();
}

void GameState::CheckCollision()
{
	if (CircleCollisionTest((player->GetX() + player->GetRadius()), (player->GetY() + player->GetRadius()),
		(enemy->GetX() + enemy->GetRadius()), (enemy->GetY() + enemy->GetRadius()), //need to add in radius to get center of rendered image for proper midpoint value
		player->GetRadius(), enemy->GetRadius())) 
	{
		player->SetCollision(true);
		enemy->SetCollision(true);
	}
	else {
		player->SetCollision(false);
		enemy->SetCollision(false);
	}
}

void GameState::CheckAttackRange()
{
	if (CircleCollisionTest((player->GetX() + player->GetAttackRange()), (player->GetY() + player->GetAttackRange()),
		(enemy->GetX() + enemy->GetAttackRange()), (enemy->GetY() + enemy->GetAttackRange()), //need to add in radius to get center of rendered image for proper midpoint value
		player->GetAttackRange(), enemy->GetAttackRange()))
	{
		enemy->SetAttack(true);
		
		if (enemy->GetAttack() == 1)
		{
			
		}
		if (enemy->GetAttack() == 2)
		{

		}
		if (enemy->GetAttack() == 3)
		{

		}
		if (enemy->GetAttack() == 4)
		{

		}
	}
	else {
		enemy->SetAttack(false);
	}
}
