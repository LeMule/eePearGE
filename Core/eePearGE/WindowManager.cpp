#include "WindowManager.h"

WindowManager::WindowManager()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}

		RenderPair renderPair;
		renderPair._window = std::make_shared<SDL_Window*>(window);
		renderPair._renderer = std::make_shared<SDL_Renderer*>(renderer);
		m_pWindowsMap.insert(std::make_pair(0, renderPair));
	}
}

WindowManager::WindowManager(int numWindows)
{
	for (int i = 0; i < numWindows; i++)
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, rand()%255+1, rand() % 255+1, rand() % 255+1, 255);
			}

			RenderPair renderPair;
			renderPair._window = std::make_shared<SDL_Window*>(window);
			renderPair._renderer = std::make_shared<SDL_Renderer*>(renderer);
			m_pWindowsMap.insert(std::make_pair(i, renderPair));
		}
	}
}

WindowManager::~WindowManager()
{
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		SDL_DestroyWindow(*(*it).second._window);
		SDL_DestroyRenderer(*(*it).second._renderer);
	}
	SDL_Quit();
}

void WindowManager::Init()
{

}

void WindowManager::Update(int context)
{
	//Update screen
	SDL_RenderPresent(*(m_pWindowsMap[context]._renderer));
}

void WindowManager::Render(int context)
{
	//Render textures to window
	SDL_RenderClear(*(m_pWindowsMap[context]._renderer));
}

void WindowManager::UpdateAllWindows()
{
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		SDL_RenderPresent(*(*it).second._renderer);
	}
}

void WindowManager::RenderAllWindows()
{
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		SDL_RenderClear(*(*it).second._renderer);
	}
}

