#include "Game.h"
#include <iostream>
#include <functional>
using namespace eePearGE;

Game::Game(const Game&)
{
	m_Velocity.first = 0.0f;
	m_Velocity.second = 0.0f;
	m_bGoFast = false;
}

Game::Game()
{
	m_Velocity.first = 0.0f;
	m_Velocity.second = 0.0f;
	m_bGoFast = false;
}

void Game::OnUpPressedEvent()
{
	float movement = -0.1f;
	m_Velocity.first = movement;
}

void Game::OnDownPressedEvent()
{
	float movement = 0.1f;
	m_Velocity.first = movement;
}

void Game::OnLeftPressedEvent()
{
	float movement = -0.1f;
	m_Velocity.second = movement;
}

void Game::OnRightPressedEvent()
{
	float movement = 0.1f;
	m_Velocity.second = movement;
}

void Game::OnUpReleasedEvent()
{
	m_Velocity.first = 0.0f;
}

void Game::OnDownReleasedEvent()
{
	m_Velocity.first = 0.0f;
}

void Game::OnLeftReleasedEvent()
{
	m_Velocity.second = 0.0f;
}

void Game::OnRightReleasedEvent()
{
	m_Velocity.second = 0.0f;
}

void Game::OnGoFastDown()
{
	m_bGoFast = true;
}

void Game::OnGoFastUp()
{
	m_bGoFast = false;
}

Game::Game(EventManagerPtr evtMngr)
{
	evtMngr->RegisterCallback("UpPressed",		std::bind(&Game::OnUpPressedEvent, this));
	evtMngr->RegisterCallback("DownPressed",	std::bind(&Game::OnDownPressedEvent, this));
	evtMngr->RegisterCallback("LeftPressed",	std::bind(&Game::OnLeftPressedEvent, this));
	evtMngr->RegisterCallback("RightPressed",	std::bind(&Game::OnRightPressedEvent, this));

	evtMngr->RegisterCallback("UpReleased",		std::bind(&Game::OnUpReleasedEvent, this));
	evtMngr->RegisterCallback("DownReleased",	std::bind(&Game::OnDownReleasedEvent, this));
	evtMngr->RegisterCallback("LeftReleased",	std::bind(&Game::OnLeftReleasedEvent, this));
	evtMngr->RegisterCallback("RightReleased",	std::bind(&Game::OnRightReleasedEvent, this));

	evtMngr->RegisterCallback("GoFastDown",		std::bind(&Game::OnGoFastDown, this));
	evtMngr->RegisterCallback("GoFastUp",		std::bind(&Game::OnGoFastUp, this));

	m_Velocity.first = 0.0f;
	m_Velocity.second = 0.0f;
	m_bGoFast = false;
}

void Game::InitGame()
{
	//Create the Player Sprite
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

	//Player Position.
	m_SpriteVec[0]->GetPosition().first = 640 / 2;
	m_SpriteVec[0]->GetPosition().second = 480 / 2;

	while (m_SpriteVec.size() < MONSTER_COUNT)
	{
		//Create the Enemies
		_data = std::shared_ptr<Sprite>(new Sprite(5, 5));
		for (int col = 1; col != 5; col++)
		{
			for (int row = 1; row != 5; row++)
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
	}

	//Position the Enemies
	for (int i = 1; i < m_SpriteVec.size(); i++)
	{
		m_SpriteVec.at(i)->SetXPosition(rand() % 640);
		m_SpriteVec.at(i)->SetYPosition(rand() % 480);
	}
};

void Game::Update()
{
	//Y Axis
	if (m_Velocity.first != 0.0)
	{
		Pear::Coord finalVelocity = m_bGoFast ? (m_Velocity.first * 2.0f) : m_Velocity.first;
		Pear::Coord updatedPosition = m_SpriteVec[0]->GetPosition().second + finalVelocity;
		if (updatedPosition > -1.0 && updatedPosition < 480)
		{
			m_SpriteVec[0]->SetYPosition(updatedPosition);
		}
	}
	
	//X Axis
	if (m_Velocity.second != 0.0)
	{
		Pear::Coord finalVelocity = m_bGoFast ? (m_Velocity.second * 2.0f) : m_Velocity.second;
		Pear::Coord updatedPosition = m_SpriteVec[0]->GetPosition().first + finalVelocity;
		if (updatedPosition > -1.0 && updatedPosition < 640)
		{
			m_SpriteVec[0]->SetXPosition(updatedPosition);
		}
	}

	//Update the Enemies too
	for (int i = 1; i < m_SpriteVec.size(); i++)
	{
		Pear::Position nextPosition = RunMonsterAI(m_SpriteVec.at(i)->GetPosition(), m_SpriteVec.at(0)->GetPosition());

		if (CheckCollision(m_SpriteVec.at(i)->GetPosition(), m_SpriteVec.at(0)->GetPosition()))
			std::cout << "You suck do better." << std::endl;

		m_SpriteVec.at(i)->SetXPosition(nextPosition.first);
		m_SpriteVec.at(i)->SetYPosition(nextPosition.second);

	}


	//Let's Gamble and Potentially add more Enemies!
	if(rand()%1000 == 0)
	{ 
		//Create the Enemy
		SpritePtr _data = std::shared_ptr<Sprite>(new Sprite(5, 5));
		for (int col = 1; col != 5; col++)
		{
			for (int row = 1; row != 5; row++)
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
		
		//Position the New Enemy
		m_SpriteVec.back()->SetXPosition(rand() % 640);
		m_SpriteVec.back()->SetYPosition(rand() % 480);
	}
}

void Game::Render()
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		m_SpriteVec[i]->RenderSprite();
	}
}

Pear::Position Game::RunMonsterAI(Pear::Position& monsterPosition, Pear::Position& playerPosition)
{
	Pear::Position newPosition;

	if (abs(monsterPosition.first - playerPosition.first) < 100 && abs(monsterPosition.second - playerPosition.second) < 100)
	{
		if (monsterPosition.first < playerPosition.first)
			newPosition.first = monsterPosition.first + 0.01;
		else
			newPosition.first = monsterPosition.first - 0.01;

		if (monsterPosition.second < playerPosition.second)
			newPosition.second = monsterPosition.second + 0.01;
		else
			newPosition.second = monsterPosition.second - 0.01;
	}
	else
	{
		newPosition.first = monsterPosition.first;
		newPosition.second = monsterPosition.second;
	}

	return newPosition;
}

bool Game::CheckCollision(Pear::Position& monsterPosition, Pear::Position& playerPosition)
{
	if (static_cast<int>(monsterPosition.first) < static_cast<int>(playerPosition.first)) return 0;
	if (static_cast<int>(monsterPosition.first) > static_cast<int>(playerPosition.first)) return 0;
	if (static_cast<int>(monsterPosition.second) < static_cast<int>(playerPosition.second)) return 0;
	if (static_cast<int>(monsterPosition.second) > static_cast<int>(playerPosition.second)) return 0;
	return 1;
}