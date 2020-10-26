#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
using namespace std;

class EndGameState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { exit };
	int final = 0;

public:
	EndGameState() { }
	EndGameState(int score);
	void Enter();
	void Exit();
	void Update();
	void Render();
};

