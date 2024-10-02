//------------------------------------------------------------------------------
//
// File Name:	WindowSystem.h
// Author(s):	Gabe Gramblicka (gabriel.gramblicka)
// Project:		GL SLOP
//
// Copyright (c) 2024 Gabe Gramblicka
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "System.h" // Inherit


#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <SDL2\SDL_main.h>

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Classes:
//------------------------------------------------------------------------------

class WindowSystem : public System {
public:
	static System& Instance();
	static bool s_isRunning;

	static SDL_Window* Window();
	static glm::ivec2 WindowSize();
	static SDL_GLContext Context();
private:
	static WindowSystem s_instance;

	static SDL_GLContext s_context;
	static SDL_Window* s_window;

	WindowSystem();
	bool Init() override;
	void Update(float dt) override;
	void Render() const override;
	void Exit() override;

	static glm::ivec2 m_windowSize;
public:
	WindowSystem(const WindowSystem& other) = delete;
	friend class Engine;
};

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
