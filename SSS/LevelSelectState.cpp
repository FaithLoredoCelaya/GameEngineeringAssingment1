#include "Game.h"
#include "LevelSelectState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "GameLevel3.h"


void LevelSelectState::Enter()
{
	cout << "Entering MainMenu...\n";
	Game::Instance()->SetLeftMouse(false);

	m_vButtons.push_back(new Button("Img/level1.png", { 0,0,870,569 }, { 312,100,400,150 }));
	m_vButtons.push_back(new Button("Img/level2.png", { 0,0,878,562 }, { 312,250,400,150 }));
	m_vButtons.push_back(new Button("Img/level3.png", { 0,0,878,562 }, { 312,400,400,150 }));
	m_vButtons.push_back(new Button("Img/return.png", { 0,0,881,567 }, { 312,600,400,150 }));
}

void LevelSelectState::Update()
{

	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::lvl1]->Clicked())
	{
		//we need to switch to gamestate ... 
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}

	else if (m_vButtons[btn::lvl2]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameLevel2());
	}

	else if (m_vButtons[btn::lvl3]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new GameLevel3());
	}

	else if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

}


void LevelSelectState::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	ScreenState::Render();
}

void LevelSelectState::Exit()
{
	cout << "Exiting MainMenu...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}