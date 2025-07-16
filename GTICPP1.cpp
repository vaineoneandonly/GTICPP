#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
import std;

SDL_Window	*w{ nullptr };
SDL_Surface *s{ nullptr };
SDL_Surface *h{ nullptr };

SDL_Rect r1{ 0, 0, 100, 100 };
float speed{ 1.0f };
std::map<std::string, bool> keyMap{
	{"up",	  false},
	{"down",  false},
	{"left",  false},
	{"right", false},
};

void handleInit()
{
	SDL_Init(SDL_INIT_VIDEO);
	w = SDL_CreateWindow("esquibamba", 1366, 768, 0);
	s = SDL_GetWindowSurface(w);

	std::string imgPath{ "white-arrow.png" };
	h = SDL_LoadBMP(imgPath.c_str());
}

void updateMap(SDL_Event &e, bool val)
{
	switch (e.key.scancode)
	{
		case SDL_SCANCODE_W: keyMap["up"]	 = val; break;
		case SDL_SCANCODE_S: keyMap["down"]  = val; break;
		case SDL_SCANCODE_A: keyMap["left"]  = val; break;
		case SDL_SCANCODE_D: keyMap["right"] = val; break;
	}
}

void moveObject(SDL_Rect &r)
{
	r1.x += keyMap["right"] * speed - keyMap["left"] * speed;
	r1.y -= keyMap["up"]	* speed - keyMap["down"] * speed;
}


int main(int argc, char* argv[])
{ 
	handleInit();

	bool running{ true };
	SDL_Event e;
	SDL_zero(e);
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if		(e.type == SDL_EVENT_QUIT)		running = false;
			else if (e.type == SDL_EVENT_KEY_DOWN)	updateMap(e, true);
			else if (e.type == SDL_EVENT_KEY_UP)	updateMap(e, false);
		}

		moveObject(r1);

		SDL_FillSurfaceRect(s, nullptr, 0x000000);
		SDL_FillSurfaceRect(s, &r1, 0xFFFFFF);
		SDL_UpdateWindowSurface(w);
	}

	return 0;
}