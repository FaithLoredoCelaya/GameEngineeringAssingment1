#include "EndGameState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "GameState.h"

EndGameState::EndGameState(int score)
{
	final = score;
}

void EndGameState::Enter()
{
	cout << "Entering EndGame...\n";

	m_pFont = TTF_OpenFont("Font/LTYPE.TTF", 50);

	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,400,400,100 }));
}

void EndGameState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		//we need to switch to gamestate ... 
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

}


void EndGameState::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	string g = "Game Over";
	string s = "Final Score: " + to_string(final);
	EndGameState::RenderFont(true, g.c_str(), 300, 150);
	EndGameState::RenderFont(true, s.c_str(), 300, 250);

	ScreenState::Render();
}

void EndGameState::Exit()
{
	cout << "Exiting EndGame...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}