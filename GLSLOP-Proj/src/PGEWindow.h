//------------------------------------------------------------------------------
//
// File Name:	PGEWindow.h
// Author(s):	Gabe Gramblicka
// Project:		Dreadit
// Course:      GAM200
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes & Forward Declarations
//------------------------------------------------------------------------------

#include "PGE.h"

//using WindowHandle = GLFWwindow;
//using MonitorHandle = GLFWmonitor;

//------------------------------------------------------------------------------
// Namespaces:
//------------------------------------------------------------------------------

namespace PGE
{
	namespace Window
	{
		// Closes the window
		// Params:
		//     handle - window handle to shut down
		//void	       Close(WindowHandle* handle);

		// Creates a new window
		// Params:
		//     width   - window width
		//     height  - window height
		//     title   - window title name
		//     monitor - monitor handle 
		//     window  - window handle
		// Returns:
		//     WindowHandle
		//WindowHandle*  Create(int width, int height, const char* title, MonitorHandle* monitor, WindowHandle* window);

		// Creates a viewport for the graphics system
		// Params:
		//     width  - width of the viewport
		//     height - height of the viewport
		void		   CreateViewport(int width, int height);

		// Gets teh primary monitor handle
		// Returns:
		//     MonitorHandle - the handle for the monitor
		//MonitorHandle* GetPrimaryMonitor();

		// Makes the window the current one
		// Params:
		//     windowHandle - window to make 
		//void		   MakeContextCurrent(WindowHandle* WindowHandle);

		// Resizes the viewport 
		// Params:
		//     handle - window to change
		//     width  - new window width
		//     height - new window height
		//void		   ResizeViewport(WindowHandle* handle, int width, int height);

		// Updates the frame controller
		// Params:
		//     handle - window to update
		//void		   UpdateFrameControl(WindowHandle* handle);


		//void           SetFocusSetCallback(WindowHandle* handle);
		//void           FocusCallback(WindowHandle* handle, int focused);
		//void           SetWindowIcon(WindowHandle* handle, GLFWimage* images);
	}
}