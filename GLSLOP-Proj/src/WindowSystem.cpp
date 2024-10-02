//------------------------------------------------------------------------------
//
// File Name:	WindowSystem.cpp
// Author(s):	Gabe Gramblicka (gabriel.gramblicka)
// Project:		GL SLOP
//
// Copyright (c) 2024 Gabe Gramblicka
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "WindowSystem.h"

#include "PGE.h"
#include "PGEWindow.h"
#include "UISystem.h" // Not the best to include another system but there's no 
					  // fast simple solution

//------------------------------------------------------------------------------
// Private Classes:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

WindowSystem WindowSystem::s_instance = WindowSystem();
bool WindowSystem::s_isRunning = true;
SDL_Window* WindowSystem::s_window = nullptr;
SDL_GLContext WindowSystem::s_context;


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

System& WindowSystem::Instance() {
	return s_instance;
}

SDL_Window* WindowSystem::Window() {
	return s_window;
}

SDL_GLContext WindowSystem::Context() {
	return s_context;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

WindowSystem::WindowSystem()
	: System("WindowSystem") {
}

bool WindowSystem::Init(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	s_window = SDL_CreateWindow("GLSLOP", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	s_context = SDL_GL_CreateContext(s_window);
	return true;
}

void WindowSystem::Update(float dt) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		UISystem::ProcessEvents(&event);
		if (event.type == SDL_QUIT) {
			s_isRunning = false;
		}
		if (event.type == SDL_WINDOWEVENT &&
			event.window.event == SDL_WINDOWEVENT_CLOSE &&
			event.window.windowID == SDL_GetWindowID(s_window)) {
			s_isRunning = false;
		}
	}
}

void WindowSystem::Render() const {
	PGE::Window::CreateViewport(600, 600);
	PGE::ClearBackground();
	SDL_GL_SwapWindow(s_window);
}

void WindowSystem::Exit() {
	SDL_GL_DeleteContext(s_context);
	SDL_DestroyWindow(s_window);
	SDL_Quit();
}
