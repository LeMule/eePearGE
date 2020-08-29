#pragma once
#include <vector>
#include "ConfigurationManager.h"
#include "WindowManager.h"

namespace eePearGE
{
	typedef std::shared_ptr<WindowManager*> WindowManagerPtr;
	typedef std::shared_ptr<ConfigurationManager*> ConfigurationManagerPtr;

	class Game;
	typedef std::shared_ptr<Game*> GamePtr;
	typedef std::vector<GamePtr> GameCatalog;

	class GameManager
	{
	public:
		GameManager(int numScreens)
		{
			m_pwindowManager = std::make_shared<WindowManager*>(new WindowManager(numScreens));
			m_pConfigurationManager = std::make_shared<ConfigurationManager*>(new ConfigurationManager());
		}

		WindowManagerPtr GetWindowManager() { return m_pwindowManager; }
		ConfigurationManagerPtr GetConfigManager() { return m_pConfigurationManager; }

		void LoadGames();

	private:
		WindowManagerPtr m_pwindowManager;
		ConfigurationManagerPtr m_pConfigurationManager;
	};
}