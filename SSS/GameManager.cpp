#include "GameManager.h"

void GameManager::TakeDamage(int dmg)
{
	hitPoints -= dmg;
}

void GameManager::SetScore(int nscore)
{
	score += nscore;
}