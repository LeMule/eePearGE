#pragma once
#include <SDL.h>

namespace eePearGE
{
	class Sprite
	{
	public:
		Sprite();

	private:
		SDL_Surface* m_spriteSheetTexture;
	};
}