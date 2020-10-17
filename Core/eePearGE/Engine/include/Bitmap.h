#ifndef _EEPEARGE_BITMAP_H_
#define _EEPEARGE_BITMAP_H_

#include <SDL.h>
#include <iostream>
namespace eePearGE
{
	class Bitmap
	{
	private:
		SDL_Surface* m_surface;
	public:
		Bitmap(std::string path)
		{
			//Load splash image
			m_surface = SDL_LoadBMP(path.c_str());
			if (m_surface == NULL)
			{
				printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
			}
		}
	};
}

#endif
