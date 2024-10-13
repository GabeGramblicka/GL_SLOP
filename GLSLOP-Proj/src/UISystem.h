﻿//------------------------------------------------------------------------------
//
// File Name:	UISystem.h
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

#include <ImGui\imgui_impl_opengl3.h> // Platform
#include <ImGui\imgui_impl_sdl2.h>	  // Renderer

#include "Data.h"

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Classes:
//------------------------------------------------------------------------------

class UISystem : public System {
public:
	static System& Instance();
	static void ProcessEvents(SDL_Event* event);
	void PrintToOutput(const std::string& message);

private:
	static UISystem s_instance;
	void ConsoleOutput();

	UISystem();
	bool Init() override;
	void Update(float dt) override;
	void Render() const override;
	void Exit() override;

	void ChooseFolder();
	void PickFolder(Dir& dir);

	void ChooseFile(ST shader);
	void PickFile(Dir& dir);

	void Clear(Dir& dir); 
	Data m_data;
public:
	UISystem(const UISystem& other) = delete;
	friend class Engine;
};

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
