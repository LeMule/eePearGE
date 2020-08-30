#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

namespace eePearGE
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int PIXEL_SCREEN_WIDTH = 256;
	const int PIXEL_SCREEN_HEIGHT = 256;

	class WindowConfig;
	typedef std::shared_ptr<SDL_Window*> WindowPtr;
	typedef std::shared_ptr<SDL_Renderer*> RendererPtr;

	struct RenderPair
	{
		WindowPtr _window;
		RendererPtr _renderer;
	};

	class Unit
	{
	public:
		std::vector<std::pair<float,float> > vertices;
		std::pair<int, int> position;
		bool updated;
	};

	struct Pixel
	{
		float r;
		float g;
		float b;
	};
	const int NUM_PIXELS = 4096; // 64x64 pixel screen.

	class WindowManager
	{
	public:
		WindowManager();
		WindowManager(int numWindows);
		~WindowManager();

		void Init();
		void InitLittleUnits();
		void InitPixelScreen();

		void UpdateAllWindows();
		void RenderAllWindows();

		void Update(int context = 0);
		void Render(int context = 0);

		void UpdatePixelScreen(Pixel data[PIXEL_SCREEN_WIDTH][PIXEL_SCREEN_HEIGHT]);
		void ClearPixelScreen(Pixel clearColor = Pixel());
		void RenderPixelScreen();
	protected:
	private:
		std::map<int, RenderPair> m_pWindowsMap;
		Pixel _pixelScreen[PIXEL_SCREEN_WIDTH][PIXEL_SCREEN_HEIGHT];
		std::map<int, Unit> m_pUnits;
		float rotationCount;
	};
}
