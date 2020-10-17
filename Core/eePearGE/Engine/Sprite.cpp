#include "Sprite.h"
#include <iostream>
#include <SDL_opengl.h>

using namespace eePearGE;

Sprite::Sprite(int width, int height)
	:_visible(true)
	,_z(0)
{
	_spriteData.resize(width);
	for (int col = 0; col < width; col++)
	{
		_spriteData.at(col).resize(height);
		for (int row = 0; row < height; row++)
		{
			_spriteData[col][row].r = static_cast<float>(0);
			_spriteData[col][row].g = static_cast<float>(0);
			_spriteData[col][row].b = static_cast<float>(0);
		}
	}
}

void Sprite::Update()
{
	//Forced Implementation. I'll Smooth this out Later(TM)
}

void Sprite::Update(std::vector<std::vector<Pixel> >& updateData)
{
	if (_spriteData.empty())
		return;

	for (int col = 1; col != _spriteData.size(); col++)
	{
		for (int row = 1; row != _spriteData.at(col).size(); row++)
		{
			_spriteData[col - 1.0][row - 1.0].r = updateData[col - 1.0][row - 1.0].r;
			_spriteData[col - 1.0][row - 1.0].g = updateData[col - 1.0][row - 1.0].g;
			_spriteData[col - 1.0][row - 1.0].b = updateData[col - 1.0][row - 1.0].b;
		}
	}
}

void Sprite::ClearSprite(Pixel clearColor)
{
	for (int col = 1; col != _spriteData.size(); col++)
	{
		for (int row = 1; row != _spriteData.at(col).size(); row++)
		{
			_spriteData[col - 1.0][row - 1.0].r = 0.f;
			_spriteData[col - 1.0][row - 1.0].g = 0.f;
			_spriteData[col - 1.0][row - 1.0].b = 0.f;
		}
	}
}

void Sprite::RenderSprite()
{
	glBegin(GL_QUADS);
	for (int col = 1; col != _spriteData.size(); col++)
	{
		for (int row = 1; row != _spriteData.at(col).size(); row++)
		{
			int finalXPos = GetPosition().first;
			int finalYPos = GetPosition().second;
			glColor4f(_spriteData[col - 1.0][row - 1.0].r, _spriteData[col - 1.0][row - 1.0].g, _spriteData[col - 1.0][row - 1.0].b, 1.f); glVertex2f(finalXPos + (1.0f + (col * 1)), finalYPos + (-1.0f + (row * 1)));
			glColor4f(_spriteData[col - 1.0][row - 1.0].r, _spriteData[col - 1.0][row - 1.0].g, _spriteData[col - 1.0][row - 1.0].b, 1.f); glVertex2f(finalXPos + (-1.0f + (col * 1)), finalYPos + (-1.0f + (row * 1)));
			glColor4f(_spriteData[col - 1.0][row - 1.0].r, _spriteData[col - 1.0][row - 1.0].g, _spriteData[col - 1.0][row - 1.0].b, 1.f); glVertex2f(finalXPos + (-1.0f + (col * 1)), finalYPos + (1.0f + (row * 1)));
			glColor4f(_spriteData[col - 1.0][row - 1.0].r, _spriteData[col - 1.0][row - 1.0].g, _spriteData[col - 1.0][row - 1.0].b, 1.f); glVertex2f(finalXPos + (1.0f + (col * 1)), finalYPos + (1.0f + (row * 1)));
		}
	}
	glEnd();
}

