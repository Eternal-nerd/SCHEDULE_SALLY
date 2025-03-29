#pragma once

#include <SDL3/SDL.h>

#include <string>

#include "gfx.h"

class Engine {
public:
	void run();

private:
	bool running_ = false;

	// Events
	SDL_Event event_;

	// Graphics
	Gfx gfx_;

	void init();
	void loop();
	void cleanup();

};