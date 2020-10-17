#ifndef _EEPEARGE_GAMEMANAGER_H_
#define _EEPEARGE_GAMEMANAGER_H_

#include <map>
#include <vector>
#include "Game.h"
#include "WindowManager.h"

namespace eePearGE
{
	class GameManager
	{
	public:
		GameManager(uint8_t numScreens = 0, /* Eh? Maybe we're making a console-output-only game...? */
				    EventManagerPtr pEvtMngr = 0)
			:m_pEvtMngr(pEvtMngr)
		{
			m_pwindowManager = new WindowManager(numScreens);
		}

		WindowManager* GetWindowManager() { return m_pwindowManager; }

		void LoadGames();
		void LoadGame(std::string gameName = "");

		Game* GetGame() { return m_pLoadedGame; }

	private:
		std::map<std::string, Game*> m_LoadedGames;
		Game* m_pLoadedGame;
		WindowManager* m_pwindowManager;
		EventManagerPtr m_pEvtMngr;
	};
}

#endif