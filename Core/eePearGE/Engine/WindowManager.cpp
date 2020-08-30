#include "WindowManager.h"
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
		window = SDL_CreateWindow("Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

		SDL_GL_CreateContext(*(m_pWindowsMap[0]._window));
		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

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
		}
		else
		{
			window = SDL_CreateWindow("Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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

			SDL_GL_CreateContext(*(m_pWindowsMap[i]._window));
			SDL_GL_SetSwapInterval(0);
			//Initialize Projection Matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

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
		SDL_DestroyWindow(*(*it).second._window);
		SDL_DestroyRenderer(*(*it).second._renderer);
	}
	SDL_Quit();
}

void WindowManager::Init()
{
	//InitLittleUnits();
	InitPixelScreen();
	rotationCount = 0.0;
}

void WindowManager::InitLittleUnits()
{
	const int UNIT_COUNT = 1000;
	for (int i = 0; i < UNIT_COUNT; i++)
	{
		Unit tempUnit;
		tempUnit.vertices.push_back(std::make_pair(5.0f, -5.0f));
		tempUnit.vertices.push_back(std::make_pair(-5.0f, -5.0f));
		tempUnit.vertices.push_back(std::make_pair(-5.0f, 5.0f));
		tempUnit.position = std::make_pair(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		m_pUnits[i] = tempUnit;
	}
}

void WindowManager::InitPixelScreen()
{
	for (int col = 0; col < PIXEL_SCREEN_WIDTH; col++)
	{
		for (int row = 0; row < PIXEL_SCREEN_HEIGHT; row++)
		{
			_pixelScreen[col][row].r = static_cast<float>(rand() % 2);
			_pixelScreen[col][row].g = static_cast<float>(rand() % 2);
			_pixelScreen[col][row].b = static_cast<float>(rand() % 2);
		}
	}
}

void WindowManager::Update(int context)
{
	//Update screen
	SDL_RenderPresent(*(m_pWindowsMap[context]._renderer));
}

void WindowManager::Render(int context)
{
	////Render textures to window
	//SDL_RenderClear(*(m_pWindowsMap[context]._renderer));
}

void WindowManager::UpdateAllWindows()
{
	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{
		/*for (int unit = 0; unit < m_pUnits.size() && !m_pUnits[unit].updated; unit++)
		{
			if (m_pUnits[unit].position.first < SCREEN_WIDTH)
				m_pUnits[unit].position.first += rand() % 5;
			else
				m_pUnits[unit].position.first -= SCREEN_WIDTH;

			if (m_pUnits[unit].position.second < SCREEN_HEIGHT)
				m_pUnits[unit].position.second += rand() % 5;
			else
				m_pUnits[unit].position.second -= SCREEN_HEIGHT;

			m_pUnits[unit].updated = true;
		}*/
	}
}

void WindowManager::RenderAllWindows()
{
	////Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::map<int, RenderPair>::iterator it = m_pWindowsMap.begin(); it != m_pWindowsMap.end(); it++)
	{		
		SDL_RenderClear(*(*it).second._renderer);
		//Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		/*int _color_swap = 0;

		for (int unit = 0; unit < m_pUnits.size(); unit++)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < m_pUnits[unit].vertices.size(); i++)
			{
				if (_color_swap == 0)
					glColor3f(1.f, 0.f, 0.f);
				else if (_color_swap == 1)
					glColor3f(0.f, 1.f, 0.f);
				else if (_color_swap == 2)
					glColor3f(0.f, 0.f, 1.f);
				else
					_color_swap = -1;
				_color_swap++;
				glVertex2f(m_pUnits[unit].vertices.at(i).first + m_pUnits[unit].position.first, m_pUnits[unit].vertices.at(i).second + m_pUnits[unit].position.second);
				m_pUnits[unit].updated = false;
			}
			glEnd();
		}*/
		ClearPixelScreen();
		Pixel _data[PIXEL_SCREEN_WIDTH][PIXEL_SCREEN_HEIGHT];
		for (int col = 1; col != PIXEL_SCREEN_WIDTH; col++)
		{
			for (int row = 1; row != PIXEL_SCREEN_HEIGHT; row++)
			{
				_data[col - 1][row - 1].r = static_cast<float>(rand() % 2);
				_data[col - 1][row - 1].g = static_cast<float>(rand() % 2);
				_data[col - 1][row - 1].b = static_cast<float>(rand() % 2);
			}
		}

		UpdatePixelScreen(_data);
		RenderPixelScreen();
		SDL_GL_SwapWindow(*(*it).second._window);
	}
}

void WindowManager::UpdatePixelScreen(Pixel data[PIXEL_SCREEN_WIDTH][PIXEL_SCREEN_HEIGHT])
{
	for (int col = 1; col != PIXEL_SCREEN_WIDTH; col++)
	{
		for (int row = 1; row != PIXEL_SCREEN_HEIGHT; row++)
		{
			_pixelScreen[col - 1][row - 1].r = data[col - 1][row - 1].r;
			_pixelScreen[col - 1][row - 1].g = data[col - 1][row - 1].g;
			_pixelScreen[col - 1][row - 1].b = data[col - 1][row - 1].b;
		}
	}
}

void WindowManager::ClearPixelScreen(Pixel clearColor)
{
	for (int col = 1; col != PIXEL_SCREEN_WIDTH; col++)
	{
		for (int row = 1; row != PIXEL_SCREEN_HEIGHT; row++)
		{
			_pixelScreen[col - 1][row - 1].r = 0.f;
			_pixelScreen[col - 1][row - 1].g = 0.f;
			_pixelScreen[col - 1][row - 1].b = 0.f;
		}
	}
}

void WindowManager::RenderPixelScreen()
{
	glBegin(GL_QUADS);
	for (int col = 1; col != PIXEL_SCREEN_WIDTH; col++)
	{
		for (int row = 1; row != PIXEL_SCREEN_HEIGHT; row++)
		{
			glColor4f(_pixelScreen[col - 1][row - 1].r, _pixelScreen[col - 1][row - 1].g, _pixelScreen[col - 1][row - 1].b, 1.f); glVertex2f(1.0f + (col * 1), -1.0f + (row * 1));
			glColor4f(_pixelScreen[col - 1][row - 1].r, _pixelScreen[col - 1][row - 1].g, _pixelScreen[col - 1][row - 1].b, 1.f); glVertex2f(-1.0f + (col * 1), -1.0f + (row * 1));
			glColor4f(_pixelScreen[col - 1][row - 1].r, _pixelScreen[col - 1][row - 1].g, _pixelScreen[col - 1][row - 1].b, 1.f); glVertex2f(-1.0f + (col * 1), 1.0f + (row * 1));
			glColor4f(_pixelScreen[col - 1][row - 1].r, _pixelScreen[col - 1][row - 1].g, _pixelScreen[col - 1][row - 1].b, 1.f); glVertex2f(1.0f + (col * 1), 1.0f + (row * 1));
		}
	}
	glEnd();
}

