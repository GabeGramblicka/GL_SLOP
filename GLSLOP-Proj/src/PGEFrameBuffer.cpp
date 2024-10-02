//------------------------------------------------------------------------------
//
// File Name:	PGEFrameBuffer.cpp
// Author(s):	Gryphon McLaughlin (i think thats how you spell it 😭)
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
#include "PGEFrameBuffer.h"

#include "WindowSystem.h"
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Static:
//------------------------------------------------------------------------------
GLuint PGE::FrameBuffer::_FBO;
GLuint PGE::FrameBuffer::_RBO;
GLuint PGE::FrameBuffer::_textureId;

//------------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------------

void PGE::FrameBuffer::CreateFrameBuffer()
{
	glm::ivec2 windowSize = WindowSystem::WindowSize();
	glGenFramebuffers(1, &_FBO);
	PGE::CheckError();
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	PGE::CheckError();

	glGenTextures(1, &_textureId);
	PGE::CheckError();
	glBindTexture(GL_TEXTURE_2D, _textureId);
	PGE::CheckError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	PGE::CheckError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	PGE::CheckError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	PGE::CheckError();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
	PGE::CheckError();

	glGenRenderbuffers(1, &_RBO);
	PGE::CheckError();
	glBindRenderbuffer(GL_RENDERBUFFER, _RBO);
	PGE::CheckError();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowSize.x, windowSize.y);
	PGE::CheckError();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _RBO);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	PGE::CheckError();
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	PGE::CheckError();
	glBindTexture(GL_TEXTURE_2D, 0);
	PGE::CheckError();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	PGE::CheckError();
}

void PGE::FrameBuffer::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	PGE::CheckError();
}

void PGE::FrameBuffer::UnbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	PGE::CheckError();
}

void PGE::FrameBuffer::RescaleFrameBuffer(GLsizei width, GLsizei height)
{
	//Camera::CameraResizeViewport(WindowSystem::Window(), width, height);
}

GLuint PGE::FrameBuffer::GetTextureId()
{
	return _textureId;
}

