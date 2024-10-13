//------------------------------------------------------------------------------
//
// File Name:	Compiler.h
// Author(s):	Gabe Gramblicka (gabriel.gramblicka)
// Project:		GL SLOP
//
// Copyright (c) 2024 Gabe Gramblicka
//
//------------------------------------------------------------------------------

#pragma once

#include "GL\glew.h"
#include "GL\GL.h"

#include "Data.h"

class Compiler {
public:
  Compiler(Dir virtDir, Dir fragDir);
  ~Compiler();
private:
  GLuint m_program;
};