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
#include "nfd\nfd.h"

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
static std::pair<std::string, bool> s_currFolder = std::make_pair("None", false);

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void ChooseFolder();
static std::pair<std::string, bool> OpenFolderDialog();

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

	ChooseFolder();

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

void ChooseFolder() {
	glm::ivec2 w = WindowSystem::WindowSize();
	if (s_currFolder.second == false) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.45f, 0.49f, 1.0f));
		s_currFolder.first = "None";
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.62f, 1.0f));
	}
	if (ImGui::Button("Choose Folder", { 110.0f, 40.0f })) {
		s_currFolder = OpenFolderDialog();
	}
	ImGui::PopStyleColor();

	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.45f, 0.49f, 1.0f));
	if (ImGui::Button("Clear", { 45.0f, 40.0f })) {
		s_currFolder.first = "None";
	}
	ImGui::PopStyleColor();

	ImGui::Text("Folder: %s", s_currFolder.first.c_str());
}

std::pair<std::string, bool> OpenFolderDialog() {
	nfdchar_t* outPath = nullptr;
	nfdresult_t result = NFD_PickFolder(NULL, &outPath);

	if (result == NFD_OKAY) {
		std::cout << "Selected folder: " << outPath << std::endl;
		std::string folder(outPath);
		free(outPath); // Don't forget to free the allocated string
		return std::make_pair(folder, true);
	}
	else if (result == NFD_CANCEL) {
		std::cout << "User canceled." << std::endl;
	}
	else {
		std::cerr << "Error: " << NFD_GetError() << std::endl;
	}
	return std::make_pair("None", true);
}
