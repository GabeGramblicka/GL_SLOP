//------------------------------------------------------------------------------
//
// File Name:	Graphics.h
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

#include <GL\glew.h> // Must come before GL.h
#include <GL\GL.h>

using GraphicsID = unsigned;

//------------------------------------------------------------------------------
// Namespaces:
//------------------------------------------------------------------------------

namespace PGE
{
	using Color = glm::vec4;

	// If an error is detected it will assert through here
	void CheckError();
	bool CheckErrorSilent();

	// Clears the background for the next frame
	void ClearBackground();

	// Sets a new background color
	// Params:
	//     Color values
	void SetBackgroundColor(PGE::Color color);
	PGE::Color GetBackgroundColor();

	float GetVecMagnitude(glm::vec2 vec);
	float GetAngle2VecRad(glm::vec2 vec0, glm::vec2 vec1);

	// Sets the blend mode for translucent objects
	// Params:
	//     mode - blendmode to choose 
	//void SetBlendMode(PGE_BlendMode mode);
}