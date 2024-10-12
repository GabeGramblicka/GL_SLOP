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
glm::ivec2 WindowSystem::m_windowSize;

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

glm::ivec2 WindowSystem::WindowSize() {
	return m_windowSize;
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
	m_windowSize = { 600, 600 };
	s_window = SDL_CreateWindow("GLSLOP", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, m_windowSize.x, m_windowSize.y,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	s_context = SDL_GL_CreateContext(s_window);

	// Init glew
	if (!PGE::LibInit()) {
		return false;
	}

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
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			m_windowSize = { event.window.data1, event.window.data2 };
		}
	}
}

void WindowSystem::Render() const {
}

void WindowSystem::Exit() {
	SDL_GL_DeleteContext(s_context);
	SDL_DestroyWindow(s_window);
	SDL_Quit();
}
