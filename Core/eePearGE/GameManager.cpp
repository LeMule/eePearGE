#include "GameManager.h"
#include "Game.h"

void GameManager::LoadGames()
{
	GamePtr newGame = std::make_shared<Game*>(new Game(m_pConfigurationManager));	
}
