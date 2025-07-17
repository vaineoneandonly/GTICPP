#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
import std;

SDL_Window	*w{ nullptr };
SDL_Surface *s{ nullptr };
SDL_Surface *h{ nullptr };

struct gameObject
{
	SDL_Rect transform;
	float		 speed;
};

struct playerObject : gameObject
{
	std::map<std::string, bool> keyMap
	{
		{"up",	  false},
		{"down",  false},
		{"left",  false},
		{"right", false},
	};
};

void handleInit()
{
	SDL_Init(SDL_INIT_VIDEO);
	w = SDL_CreateWindow("esquibamba", 1366, 768, 0);
	s = SDL_GetWindowSurface(w);

	std::string imgPath{ "white-arrow.png" };
	h = SDL_LoadBMP(imgPath.c_str());
}

void updateMap(SDL_Event &e, bool val, playerObject &p)
{
	switch (e.key.scancode)
	{
		case SDL_SCANCODE_W: p.keyMap["up"]	   = val; break;
		case SDL_SCANCODE_S: p.keyMap["down"]  = val; break;
		case SDL_SCANCODE_A: p.keyMap["left"]  = val; break;
		case SDL_SCANCODE_D: p.keyMap["right"] = val; break;
	}
}

void movePlayerObject(playerObject &p)
{
	p.transform.x += p.keyMap["right"] * p.speed - p.keyMap["left"] * p.speed;
	p.transform.y -= p.keyMap["up"]	   * p.speed - p.keyMap["down"] * p.speed;
}


int main(int argc, char* argv[])
{ 
	handleInit();

	playerObject player;
	player.transform = { 0, 0, 100, 100 };
	player.speed = 1.0f;

	bool running{ true };
	SDL_Event e;
	SDL_zero(e);
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)		running = false;
			else if (e.type == SDL_EVENT_KEY_DOWN)	updateMap(e, true, player);
			else if (e.type == SDL_EVENT_KEY_UP)
			{
				updateMap(e, false, player);
				switch (e.key.scancode)
				{
					case SDL_SCANCODE_F: 
						std::cout << "foi";
						gameObject *ngo = new gameObject;
						ngo -> transform = { SDL_rand(1366), SDL_rand(768), 10, 10 };
						SDL_FillSurfaceRect(s, &ngo -> transform, 0xFFFF00);
						break;
				}
			}
			else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				switch (e.button.button)
				{
					case SDL_BUTTON_LEFT:  player.speed += 1.0f; break;
					case SDL_BUTTON_RIGHT: player.speed -= 1.0f; break;
				}
			}

		}

		movePlayerObject(player);

		SDL_FillSurfaceRect(s, nullptr, 0x000000);
		SDL_FillSurfaceRect(s, &(player.transform), 0xFFFFFF);
		SDL_UpdateWindowSurface(w);
	}

	return 0;
}