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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

System& WindowSystem::Instance() {
	return s_instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

WindowSystem::WindowSystem()
	: System("WindowSystem")
	, m_context()
	, m_window () {
}

bool WindowSystem::Init(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	m_window = SDL_CreateWindow("GLSLOP", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	m_context = SDL_GL_CreateContext(m_window);
	return true;
}

void WindowSystem::Update(float dt) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			s_isRunning = false;
			break;
		}
	}
	SDL_GL_SwapWindow(m_window);
}

void WindowSystem::Render() const
{
}

void WindowSystem::Exit() {
	SDL_GL_DeleteContext(m_context);
	SDL_Quit();
}
