#ifndef _EEPEARGE_GAME_H_
#define _EEPEARGE_GAME_H_

#include "EventManager.h"
#include "Sprite.h"
#include <memory>

namespace eePearGE
{
	class Game
	{
	public:
		const int MONSTER_COUNT = 20;
		Game(EventManagerPtr evtMngr);
		~Game(){};

		void Update();
		void Render();

		//Movement Key Down
		void OnUpPressedEvent();
		void OnDownPressedEvent();
		void OnLeftPressedEvent();
		void OnRightPressedEvent();
		
		//Movement Key Up
		void OnUpReleasedEvent();
		void OnDownReleasedEvent();
		void OnLeftReleasedEvent();
		void OnRightReleasedEvent();

		void OnGoFastDown();
		void OnGoFastUp();

		Pear::Position RunMonsterAI(Pear::Position& monsterPosition, Pear::Position& playerPosition);
		bool CheckCollision(Pear::Position& monsterPosition, Pear::Position& playerPosition);

		virtual void InitGame();
	private:
		Game(const Game&);
		Game();

		std::vector<SpritePtr> m_SpriteVec;
		std::pair<float, float> m_Velocity;
		bool m_bGoFast;
	};
	//typedef std::shared_ptr<Game> GamePtr;
}

#endif