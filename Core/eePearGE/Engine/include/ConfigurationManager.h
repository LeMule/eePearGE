#ifndef _EEPEARGE_CONFIGURATIONMANAGER_H_
#define _EEPEARGE_CONFIGURATIONMANAGER_H_

#include "tinyxml2.h"
#include <string>
#include <memory>
namespace eePearGE
{
	class GameConfig
	{
	public:
		uint32_t _gameID;
		uint32_t _numScreens;
		std::string _gameName;
	};

	class ConfigurationManager
	{
	public:
		GameConfig LoadGameConfig(std::string game_path)
		{
			GameConfig cfg = GameConfig();
			cfg._gameName = std::string("SampleGame").c_str();
			cfg._gameID = 1;
			cfg._numScreens = 2;
			return cfg;
		}
	};

	//typedef std::shared_ptr<ConfigurationManager> ConfigurationManagerPtr;
}

#endif