//------------------------------------------------------------------------------
//
// File Name:	PGEWindow.cpp
// Author(s):	Gabe Gramblicka
// Project:     Dreadit
// Course:		GAM200
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PGEWindow.h"

using namespace PGE;

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

//void Window::Close(WindowHandle* handle)
//{
//    // Close the window
//    glfwDestroyWindow(handle);
//}
//
//
//
//WindowHandle* Window::Create(int width, int height, const char* title, MonitorHandle* monitor, WindowHandle* window)
//{
//    return glfwCreateWindow(width, height, title, monitor, window);
//}

void Window::CreateViewport(int width, int height)
{
    // Create the viewport at the specified size
    glViewport(0, 0, width, height);
    //PGE::CheckError();
}

//GLFWmonitor* PGE::Window::GetPrimaryMonitor()
//{
//    return glfwGetPrimaryMonitor();
//}
//
//void Window::MakeContextCurrent(WindowHandle* GLFWwindow)
//{
//    // Make this window's OpenGL context the current one
//    glfwMakeContextCurrent(GLFWwindow);
//}
//
//void Window::ResizeViewport(WindowHandle* handle, int width, int height)
//{
//    // Call our function to set up the viewport
//    Camera::CameraResizeViewport(handle, width, height);
//
//    // Set this function to be called again whenever the window size changes
//    glfwSetFramebufferSizeCallback(handle, Camera::CameraResizeViewport);
//    // returns true if no short circuits are hit
//}
//
//void Window::UpdateFrameControl(WindowHandle* handle)
//{
//    // Handle the window events
//    glfwPollEvents();
//
//    // Swap the buffers to display everything from the current loop on the screen
//    glfwSwapBuffers(handle);
//}
//
//void PGE::Window::SetFocusSetCallback(WindowHandle* handle)
//{
//    glfwSetWindowFocusCallback(handle, FocusCallback);
//}
//
//void PGE::Window::FocusCallback(WindowHandle* handle, int focused)
//{
//    SceneSystem::SetSuspended(!focused); // Inverse since we are unsuspending on focus
//    PSE::SetCategoryPaused(PSE::MASTER, !focused); // Inverse since we are unpausing on focus
//}
//
//void PGE::Window::SetWindowIcon(WindowHandle* handle, GLFWimage* images)
//{
//    glfwSetWindowIcon(handle, 1, images);
//}

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------

