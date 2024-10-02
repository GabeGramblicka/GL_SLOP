//------------------------------------------------------------------------------
//
// File Name:	PGEFrameBuffer.h
// Author(s):	Nick Brennan, Gryphon McLaughlin
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

//------------------------------------------------------------------------------
// Namespaces:
//------------------------------------------------------------------------------
namespace PGE
{
	class FrameBuffer 
	{
	public:
		static void CreateFrameBuffer();

		static void BindFrameBuffer();
		static void UnbindFrameBuffer();

		static void RescaleFrameBuffer(GLsizei, GLsizei);

		static GLuint GetTextureId();
	private:
		static GLuint _FBO;
		static GLuint _RBO;
		static GLuint _textureId;
	};
}
