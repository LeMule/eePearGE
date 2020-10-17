#include <memory>
#include "GameManager.h"
#include "Game.h"

using namespace eePearGE;

void GameManager::LoadGames()
{
	m_LoadedGames["SampleGame"] = new Game(m_pEvtMngr);
}

void GameManager::LoadGame(std::string gameName)
{
	if (m_LoadedGames.find(gameName) != m_LoadedGames.end())
	{
		m_pLoadedGame = m_LoadedGames.at(gameName);
		m_pLoadedGame->InitGame();
	}
}
