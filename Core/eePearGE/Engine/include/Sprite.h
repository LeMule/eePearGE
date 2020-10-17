#ifndef _EEPEARGE_SPRITE_H_
#define _EEPEARGE_SPRITE_H_

#include <SDL.h>
#include <vector>
#include <memory>
#include "Pear.h"

namespace eePearGE
{
	//This is not my home, find me a home please.
	struct Pixel
	{
		float r;
		float g;
		float b;
		float a;
	};

	//typedef std::shared_ptr<Sprite> SpritePtr;
	class Sprite : public Pear
	{

	public:
		Sprite(int width, int height);
		
		//There are a few ways to update a sprite...
		virtual void Update();
		virtual void Update(std::vector<std::vector<Pixel> >& updateData = std::vector<std::vector<Pixel> >());
		void ClearSprite(Pixel clearColor = Pixel());
		void RenderSprite();

		std::vector<std::vector<Pixel> >& GetSpriteData() { return _spriteData; }

		bool IsVisible() const { return _visible; }
		void SetVisibility(bool set) { _visible = set; }
		
		uint8_t GetZValue() const { return _z; }

	private:
		bool _visible;
		uint8_t _z;
		std::vector<std::vector<Pixel> > _spriteData;
	};

	typedef std::shared_ptr<Sprite> SpritePtr;
}

#endif