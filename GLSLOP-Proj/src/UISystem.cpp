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
	const char* glsl_version = "#version 430";
	
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

	ImGui::Begin("Dockspace", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTabs);
	ImGui::DockSpace(ImGui::GetID("Dockspace"));
	ImGui::SetWindowSize(ImVec2(wSize.x, wSize.y));

	ChooseFolder();
	ConsoleOutput();

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

void UISystem::ChooseFolder() {
	ImGui::Begin("Choose Folder");

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

	ImGui::End();
}

void UISystem::ConsoleOutput() {
	ImGui::Begin("Console Output");

	// Set console appearance
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark background
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White text

	// Create a scrollable area
	ImGui::BeginChild("OutputChild", ImVec2(0, 300), true); // 300 pixels height, scrollable
	ImGui::Text("%s", m_outputBuffer.str().c_str());

	// Scroll to bottom if autoScroll is enabled
	if (true) {
		ImGui::SetScrollHereY(1.0f); // Scroll to bottom
	}
	ImGui::EndChild();

	ImGui::PopStyleColor(2); // Restore previous styles

	ImGui::End();
}

std::pair<std::string, bool> UISystem::OpenFolderDialog() {
	nfdchar_t* outPath = nullptr;
	nfdresult_t result = NFD_PickFolder(NULL, &outPath);

	if (result == NFD_OKAY) {
		m_outputBuffer << "Selected folder: " << outPath << std::endl;
		std::string folder(outPath);
		free(outPath); // Don't forget to free the allocated string
		return std::make_pair(folder, true);
	}
	else if (result == NFD_CANCEL) {
		m_outputBuffer << "User canceled." << std::endl;
	}
	else {
		m_outputBuffer << "Error: " << NFD_GetError() << std::endl;
	}
	return std::make_pair("None", true);
}

void UISystem::PrintToOutput(const std::string& message) {
    m_outputBuffer << message << std::endl;

    // Limit the number of lines in the output
    if (std::count(m_outputBuffer.str().begin(), m_outputBuffer.str().end(), '\n') > 100) {
		m_outputBuffer.str(""); // Clear the buffer
		m_outputBuffer.clear(); // Clear any error flags
    }
}
