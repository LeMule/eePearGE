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
		Game(EventManagerPtr evtMngr);
		~Game(){};

		void Update();
		void Render();

		void DummyOnUpEvent();
		void DummyOnDownEvent();
		void DummyOnLeftEvent();
		void DummyOnRightEvent();

		virtual void InitGame() 
		{
			SpritePtr _data = std::shared_ptr<Sprite>(new Sprite(20, 20));
			for (int col = 1; col != 20; col++)
			{
				for (int row = 1; row != 20; row++)
				{
					if (rand() % 25)
					{
						_data->GetSpriteData()[col - 1.0][row - 1.0].r = static_cast<float>(rand() % 2);
						_data->GetSpriteData()[col - 1.0][row - 1.0].g = static_cast<float>(rand() % 2);
						_data->GetSpriteData()[col - 1.0][row - 1.0].b = static_cast<float>(rand() % 2);
					}
					else
					{
						_data->GetSpriteData()[col - 1.0][row - 1.0].r = static_cast<float>(0);
						_data->GetSpriteData()[col - 1.0][row - 1.0].g = static_cast<float>(0);
						_data->GetSpriteData()[col - 1.0][row - 1.0].b = static_cast<float>(0);
					}
				}
			}
			m_SpriteVec.push_back(_data);
		};
	private:
		Game(const Game&);
		Game();

		std::vector<SpritePtr> m_SpriteVec;
	};
	//typedef std::shared_ptr<Game> GamePtr;
}

#endif