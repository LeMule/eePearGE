#include <iostream>
#include <chrono>
#include <xhash>
#include "GameManager.h"

using namespace eePearGE;
using namespace std::chrono_literals;
// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(100ms);
std::unique_ptr<GameManager*> pGameManager;

struct game_state
{
	// this contains the state of your game, such as positions and velocities
};

bool handle_events(EventManagerPtr evtPtr)
{
	 //Handle events on queue
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			return true; // true if the user wants to quit the game
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDL_KeyCode::SDLK_UP:
				evtPtr->QueueEvent("Up");
				break;
			case SDL_KeyCode::SDLK_DOWN:
				evtPtr->QueueEvent("Down");
				break;
			case SDL_KeyCode::SDLK_LEFT:
				evtPtr->QueueEvent("Left");
				break;
			case SDL_KeyCode::SDLK_RIGHT:
				evtPtr->QueueEvent("Right");
				break;
			}
		}
	}
	return false; 
}

void update(game_state*, EventManagerPtr evtPtr)
{
	//Pump a queue'd event first so it propagates pre-Update.
	evtPtr->Pump();
	(*pGameManager)->GetWindowManager()->UpdateAllWindows((*pGameManager)->GetGame());
}

void render(game_state const&)
{
	(*pGameManager)->GetWindowManager()->RenderAllWindows((*pGameManager)->GetGame());
}

game_state interpolate(game_state const& current, game_state const& previous, float alpha)
{
	game_state interpolated_state;

	// interpolate between previous and current by alpha here

	return interpolated_state;
}

int main(int argc, char* args[])
{
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds frame(0ms);
	std::chrono::nanoseconds frame_dur(33ms);
	auto time_since_last_frame = clock::now();
	bool quit_game = false;

	game_state current_state;
	game_state previous_state;

	EventManagerPtr evtMngr = std::shared_ptr<WordEventManager>(new WordEventManager());
	pGameManager = std::make_unique<GameManager*>(new GameManager(1, evtMngr));
	(*pGameManager)->LoadGames();
	(*pGameManager)->LoadGame("SampleGame");

	while (!quit_game) 
	{
		do 
		{
			auto delta_time = clock::now() - time_since_last_frame;
			time_since_last_frame = clock::now();
			quit_game = handle_events(evtMngr);

			frame += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

			previous_state = current_state;
			update(&current_state, evtMngr);

		} while (frame < timestep);

		// calculate how close or far we are from the next timestep
		auto alpha = (float)frame.count() / timestep.count();

		frame = 0ms;
		auto interpolated_state = interpolate(current_state, previous_state, alpha);

		render(interpolated_state);
	}

	return 0;
}