//------------------------------------------------------------------------------
//
// File Name:	PGE.cpp
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
#include "PGE.h"

static PGE::Color bgcolor{ 0.0f, 0.0f, 0.0f, 0.0f };

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

void PGE::CheckError()
{
#if _DEBUG 
    // Get the current error value
    GLenum error = glGetError();
    // Check if there is an error
    if (error != GL_NO_ERROR)
    {
        // Print the error value to the console
        std::cout << "Error: " << error << std::endl;
        // Use assert to stop the program so we can see what is happening
        assert(false);
    }
#endif
}

bool PGE::CheckErrorSilent()
{
#if _DEBUG 
    // Get the current error value
    GLenum error = glGetError();
    // Check if there is an error
    if (error != GL_NO_ERROR)
    {
        return true;
    }
    return false;
#endif
}

void PGE::ClearBackground()
{
    glClear(GL_COLOR_BUFFER_BIT);
    PGE::CheckError();
}

void PGE::SetBackgroundColor(PGE::Color color)
{
    bgcolor = color;
    glClearColor(color.r, color.g, color.b, color.a);
    PGE::CheckError();
}

PGE::Color PGE::GetBackgroundColor(void)
{
    return bgcolor;
}

//------------------------------------------------------------------------------
// Private Functions
//------------------------------------------------------------------------------

//----------------------------------------------------------------------------//
// OpenGL Example used in this file                                           //
//----------------------------------------------------------------------------//
