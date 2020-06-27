#pragma once
#include <vector>
#include "ConfigurationManager.h"
#include "WindowManager.h"

typedef std::shared_ptr<WindowManager*> WindowManagerPtr;
typedef std::shared_ptr<ConfigurationManager*> ConfigurationManagerPtr;
//typedef std::vector<GamePtr> GameCatalog;

class Game;
typedef std::shared_ptr<Game*> GamePtr;

class GameManager
{
public:
	GameManager() 
	{
		m_pwindowManager = std::make_shared<WindowManager*>(new WindowManager(3));
		m_pConfigurationManager = std::make_shared<ConfigurationManager*>(new ConfigurationManager());
	}

	WindowManagerPtr GetWindowManager() { return m_pwindowManager; }
	ConfigurationManagerPtr GetConfigManager() { return m_pConfigurationManager; }

	void LoadGames();

private:
	WindowManagerPtr m_pwindowManager;
	ConfigurationManagerPtr m_pConfigurationManager;
};

