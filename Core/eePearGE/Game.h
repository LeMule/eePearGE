#pragma once
#include "GameManager.h"
#include <memory>

class Game
{
public:
	Game(ConfigurationManagerPtr cfgMgr);
	~Game() {};

	virtual void InitGame() {};
private:
	Game(const Game&);
	void SetGameConfig(GameConfig cfg) { gameConfig = cfg; };
	GameConfig gameConfig;
};

