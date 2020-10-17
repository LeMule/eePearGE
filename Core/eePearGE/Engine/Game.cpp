#include "Game.h"
#include <iostream>
#include <functional>
using namespace eePearGE;

void Game::DummyOnUpEvent()
{
	m_SpriteVec[0]->SetYPosition(m_SpriteVec[0]->GetPosition().second - 1);
}

void Game::DummyOnDownEvent()
{
	m_SpriteVec[0]->SetYPosition(m_SpriteVec[0]->GetPosition().second + 1);
}

void Game::DummyOnLeftEvent()
{
	m_SpriteVec[0]->SetXPosition(m_SpriteVec[0]->GetPosition().first - 1);
}

void Game::DummyOnRightEvent()
{
	m_SpriteVec[0]->SetXPosition(m_SpriteVec[0]->GetPosition().first + 1);
}

Game::Game(EventManagerPtr evtMngr)
{
	evtMngr->RegisterCallback("Up", std::bind(&Game::DummyOnUpEvent, this));
	evtMngr->RegisterCallback("Down", std::bind(&Game::DummyOnDownEvent, this));
	evtMngr->RegisterCallback("Left", std::bind(&Game::DummyOnLeftEvent, this));
	evtMngr->RegisterCallback("Right", std::bind(&Game::DummyOnRightEvent, this));
}

void Game::Update()
{
	
}

void Game::Render()
{
	m_SpriteVec[0]->RenderSprite();
}