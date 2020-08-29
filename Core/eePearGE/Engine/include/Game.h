#pragma once
#include "GameManager.h"
#include <memory>

namespace eePearGE
{
	class Game
	{
	public:
		Game(ConfigurationManagerPtr cfgMgr);
		Game(GameConfig cfg);
		~Game() {};

		virtual void InitGame() {};
	private:
		Game(const Game&);
		Game();

		void SetGameConfig(GameConfig cfg) { m_gameConfig = cfg; };
		GameConfig m_gameConfig;
	};
}