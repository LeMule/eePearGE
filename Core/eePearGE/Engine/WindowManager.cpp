#include "WindowManager.h"
#include "GameManager.h"
#include <SDL_opengl.h>
using namespace eePearGE;

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
		window = SDL_CreateWindow("Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, SDL_WINDOW_SHOWN);
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
		renderPair._window = window;
		renderPair._renderer = renderer;
		m_pWindowsMap.insert(std::make_pair(0, renderPair));

		SDL_GL_CreateContext(m_pWindowsMap[0]._window);
		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 0.0, 1.0, -1.0);

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error initializing OpenGL! %s\n", SDL_GetError());
		}
	}
	Init();
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
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			window = SDL_CreateWindow("Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, SDL_WINDOW_OPENGL);
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
			renderPair._window = window;
			renderPair._renderer = renderer;
			m_pWindowsMap.insert(std::make_pair(i, renderPair));

			SDL_GL_CreateContext(m_pWindowsMap[i]._window);
			SDL_GL_SetSwapInterval(0);
			//Initialize Projection Matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 0.0, 1.0, -1.0);

			//Initialize Modelview Matrix
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//Initialize clear color
			glClearColor(0.f, 0.f, 0.f, 1.f);

			//Check for error
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				printf("Error initializing OpenGL! %s\n", SDL_GetError());
			}
		}
	}
	Init();
}

WindowManager::~WindowManager()
{
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		SDL_DestroyWindow((*it).second._window);
		SDL_DestroyRenderer((*it).second._renderer);
	}
	SDL_Quit();
}

void WindowManager::Init()
{
	rotationCount = 0.0;
}

void WindowManager::Update(Game* gme, int context)
{
	//Update screen
	gme->Update();
	SDL_RenderPresent(m_pWindowsMap[context]._renderer);
}

void WindowManager::Render(Game* gme, int context)
{
	////Render textures to window
	gme->Render();
	SDL_RenderClear(m_pWindowsMap[context]._renderer);
}

void WindowManager::UpdateAllWindows(Game* gme)
{
	gme->Update();
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		
	}
}

void WindowManager::RenderAllWindows(Game* gme)
{
	////Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gme->Render();
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{		
		SDL_RenderClear((*it).second._renderer);
		//Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		SDL_GL_SwapWindow((*it).second._window);
	}
}