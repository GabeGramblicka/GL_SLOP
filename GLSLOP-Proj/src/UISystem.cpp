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
#include "PGEFrameBuffer.h"

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
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	
	ImGui_ImplSDL2_InitForOpenGL(WindowSystem::Window(), WindowSystem::Context());
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	ImVec2 wSize(300.0f, 500.0f);
	ImGui::SetNextWindowSize(wSize);

	PGE::FrameBuffer::CreateFrameBuffer();

	return true;
}

void UISystem::Update(float dt) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	static ImVec2 s_gamePos;
	static ImVec2 s_gameSize = { 180, 200 };

	if (s_showDemoWindow) {
		//ImGui::ShowDemoWindow(&s_showDemoWindow);
	//}
	//
	//{
		// Pre-Window Variables and Settings
		glm::ivec2 appSize = WindowSystem::WindowSize();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

		// So it's easier to drag
		ImGui::SetNextWindowSize(ImVec2(appSize.x, appSize.y));

		// Create window
		if (ImGui::Begin("Game Preview"))
		{
			ImVec2 contentRegion = ImGui::GetContentRegionAvail();
			s_gamePos = ImGui::GetWindowPos();

			// Calculate the aspect ratio of the image and the actual window
			float imageAspectRatio = static_cast<float>(appSize.x) / static_cast<float>(appSize.y);
			float paddingAspectRatio = contentRegion.x / contentRegion.y;

			// Set the viewport 
			glViewport(0, 0, appSize.x, appSize.y);

			// Either the x or the y will be adjusted but not both
			ImVec2 padding{ 0.0f, 0.0f };

			// Scaling window horizontally
			if (paddingAspectRatio >= imageAspectRatio)
			{
				float imageWidth = contentRegion.y * imageAspectRatio;
				padding.x = (contentRegion.x - imageWidth) / 2;
				s_gameSize = { imageWidth , contentRegion.y };

				ImVec2 cursorPos = ImGui::GetCursorPos() + ImVec2{ padding.x, 0 };
				s_gamePos += cursorPos;
				ImGui::SetCursorPosX(cursorPos.x);
			}
			// Scaling window vertically
			else // (paddingAspectRatio < imageAspectRatio)
			{
				float imageHeight = contentRegion.x / imageAspectRatio;
				padding.y = (contentRegion.y - imageHeight) / 2;
				s_gameSize = { contentRegion.x, imageHeight };

				float cursorPosY = ImGui::GetCursorPosY() + padding.y;
				s_gamePos.y += cursorPosY;
				ImGui::SetCursorPosY(cursorPosY);
			}
			// Finally render the frame buffer
			ImGui::Image((ImTextureID)(intptr_t)PGE::FrameBuffer::GetTextureId(), s_gameSize, { 0, 1 }, { 1, 0 });

			//ImGui::GetForegroundDrawList()->AddRect(_gamePos, _gamePos + _gameSize, WarningColorU32());
		}
		ImGui::End();

		// Window padding and rounding
		ImGui::PopStyleVar(2);
	}

	ImGui::EndFrame();
}

void UISystem::Render() const {
	PGE::FrameBuffer::UnbindFrameBuffer();

	PGE::ClearBackground();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	PGE::FrameBuffer::BindFrameBuffer();

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void UISystem::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
