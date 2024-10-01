//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Gabe Gramblicka (gabriel.gramblicka)	
//
// Copyright (c) Gabe Gramblicka
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <SDL2\SDL_main.h>
#include <GL\glew.h> // Must come before GL.h
#include <GL\GL.h>

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("GLSLOP", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	bool done = false;
	Uint32 ticksLast = SDL_GetTicks();
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			}
		}
		Uint32 ticks = SDL_GetTicks();
		double dt = 0.001 * (ticks - ticksLast);
		ticksLast = ticks;
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------