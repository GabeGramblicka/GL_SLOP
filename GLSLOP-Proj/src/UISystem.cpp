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

	ImGui::Begin("Dockspace", nullptr, ImGuiWindowFlags_NoMove
								     | ImGuiWindowFlags_NoResize
								     | ImGuiWindowFlags_NoTitleBar);
	ImGui::DockSpace(ImGui::GetID("Dockspace"));
	ImGui::SetWindowSize(ImVec2(wSize.x, wSize.y));

	ImGui::Begin("Choose Folder");
	ChooseFolder();
	ConsoleOutput();
	ImGui::End();

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
  glm::ivec2 w = WindowSystem::WindowSize();

  PickFolder(m_data[FOLDER]);

  ImGui::SameLine();
  Clear(m_data[FOLDER]);

  ImGui::Text("Folder: %s", m_data[FOLDER].first.c_str());

}

void UISystem::PickFolder(Dir& dir) {
  if (dir.second == false) {
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.45f, 0.49f, 1.0f));
	dir.first = "None";
  }
  else {
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.62f, 1.0f));
  }
  if (ImGui::Button("Choose Folder", { 110.0f, 40.0f })) {
	dir = Data::OpenFolderDialog(m_data.OB());
  }
  ImGui::PopStyleColor();
}

void UISystem::ChooseFile(ST shader) {
  glm::ivec2 w = WindowSystem::WindowSize();

  PickFolder(m_data[FOLDER]);

  ImGui::SameLine();
  Clear(m_data[FOLDER]);

  ImGui::Text("Folder: %s", m_data[FOLDER].first.c_str());
}

void UISystem::PickFile(Dir& dir) {
}

void UISystem::Clear(Dir& dir) {
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.85f, 0.45f, 0.49f, 1.0f));
  if (ImGui::Button("Clear", { 45.0f, 40.0f })) {
	if (dir.second == false) {
	  m_data.OB() << "Nothing to clear" << std::endl;
	}
	else {
	  m_data.OB() << "Cleared" << std::endl;
	}
	dir.first = "None";
	dir.second = false;
  }

  ImGui::PopStyleColor();
}

void UISystem::ConsoleOutput() {
	ImGui::Begin("Console Output");

	// Set console appearance
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark background
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White text

	// Create a scrollable area
	ImGui::BeginChild("OutputChild", ImVec2(0, 300), true); // 300 pixels height, scrollable
	ImGui::Text("%s", m_data.OB().str().c_str());

	// Scroll to bottom if autoScroll is enabled
	if (true) {
		ImGui::SetScrollHereY(1.0f); // Scroll to bottom
	}
	ImGui::EndChild();

	ImGui::PopStyleColor(2); // Restore previous styles

	ImGui::End();
}

void UISystem::PrintToOutput(const std::string& message) {
	m_data.OB() << message << std::endl;

    // Limit the number of lines in the output
    if (std::count(m_data.OB().str().begin(), m_data.OB().str().end(), '\n') > 100) {
		m_data.OB().str(""); // Clear the buffer
		m_data.OB().clear(); // Clear any error flags
    }
}