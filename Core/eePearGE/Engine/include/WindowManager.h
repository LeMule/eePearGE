#ifndef _EEPEARGE_WINDOWMANAGER_H_
#define _EEPEARGE_WINDOWMANAGER_H_

#include <SDL.h>
#include <map>
#include <vector>
#include <memory>
#include "Game.h"

namespace eePearGE
{
	const int VIEWPORT_WIDTH = 640;
	const int VIEWPORT_HEIGHT = 480;

	class WindowConfig;
	class Sprite;

	struct RenderPair
	{
		SDL_Window* _window;
		SDL_Renderer* _renderer;
	};

	class Unit
	{
	public:
		std::vector<std::pair<float,float> > vertices;
		std::pair<int, int> position;
		bool updated;
	};

	const int NUM_PIXELS = 4096; // 64x64 pixel screen.

	class WindowManager
	{
	public:
		WindowManager();
		WindowManager(int numWindows);
		~WindowManager();

		void Init();
		/*void InitLittleUnits();*/ //Delete me later.

		void UpdateAllWindows(Game* gme);
		void RenderAllWindows(Game* gme);

		void Update(Game* gme, int context = 0);
		void Render(Game* gme, int context = 0);

	protected:
	private:
		std::map<int, RenderPair> m_pWindowsMap;
		std::vector<Sprite*> m_sprites; //Will draw on every window
		/*std::map<int, Unit> m_pUnits;*/
		float rotationCount;
	};
}

#endif
