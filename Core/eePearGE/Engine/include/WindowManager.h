#pragma once
#include <SDL.h>
#include <map>
#include <memory>

namespace eePearGE
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	class WindowConfig;
	typedef std::shared_ptr<SDL_Window*> WindowPtr;
	typedef std::shared_ptr<SDL_Renderer*> RendererPtr;

	struct RenderPair
	{
		WindowPtr _window;
		RendererPtr _renderer;
	};

	class WindowManager
	{
	public:
		WindowManager();
		WindowManager(int numWindows);
		~WindowManager();

		void Init();

		void UpdateAllWindows();
		void RenderAllWindows();

		void Update(int context = 0);
		void Render(int context = 0);
	protected:
	private:
		std::map<int, RenderPair> m_pWindowsMap;
	};
}
