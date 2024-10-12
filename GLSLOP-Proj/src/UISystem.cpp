//------------------------------------------------------------------------------
//
// File Name:	UISystem.cpp
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
#include "UISystem.h"

#include "WindowSystem.h"
#include "PGE.h"
#include "PGEWindow.h"

//------------------------------------------------------------------------------
// Private Classes:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

UISystem UISystem::s_instance = UISystem();

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static bool s_showDemoWindow = true;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

System& UISystem::Instance() {
	return s_instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void UISystem::ProcessEvents(SDL_Event* event) {
	ImGui_ImplSDL2_ProcessEvent(event);
}

UISystem::UISystem()
 : System("UISystem") {
}

bool UISystem::Init() {
	// Setup ImGui
	const char* glsl_version = "#version 330";
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	
	ImGui_ImplSDL2_InitForOpenGL(WindowSystem::Window(), WindowSystem::Context());
	ImGui_ImplOpenGL3_Init(glsl_version);

	return true;
}

void UISystem::Update(float dt) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	glm::ivec2 wSize = WindowSystem::WindowSize();
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(wSize.x, wSize.y));

	// Create a borderless, non-resizable ImGui window
	ImGui::Begin("FullScreenWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::End();
}

void UISystem::Render() const {
	ImGui::Render();

	glm::ivec2 wSize = WindowSystem::WindowSize();
	PGE::Window::CreateViewport(wSize.x, wSize.y);

	PGE::SetBackgroundColor(PGE::Color(0.15f));
	PGE::ClearBackground();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(WindowSystem::Window());
}

void UISystem::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
