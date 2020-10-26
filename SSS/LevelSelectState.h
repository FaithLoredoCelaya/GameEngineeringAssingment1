#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
using namespace std;

class LevelSelectState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { lvl1, lvl2, lvl3, exit };
public:
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};

