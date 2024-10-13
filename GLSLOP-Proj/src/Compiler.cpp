//------------------------------------------------------------------------------
//
// File Name:	Compiler.cpp
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
#include "Compiler.h"

#include "Data.h"

//------------------------------------------------------------------------------
// Private Classes:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

Compiler::Compiler(Dir virtDir, Dir fragDir)
: m_program(0) {

  Data::OB() << "Reading fragment file..." << std::endl;
  GLuint& program = m_program;
  std::ifstream fragmentShaderFile(virtDir.first.c_str());
  std::stringstream fragmentShaderData;
  fragmentShaderData << fragmentShaderFile.rdbuf();
  fragmentShaderFile.close();
  std::string shaderString = fragmentShaderData.str();
  const char* shaderText = shaderString.c_str();
  GLint textLength = (GLint)shaderString.size();
  Data::OB() << "Compiling fragment shader..." << std::endl;
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &shaderText, &textLength);
  glCompileShader(frag);
  Data::OB() << "Fragment shader compiled successfully" << std::endl;

  Data::OB() << "Reading vertex file..." << std::endl;
  std::ifstream vertexShaderFile(virtDir.first.c_str()); 
  std::stringstream vertexShaderData;             
  vertexShaderData << vertexShaderFile.rdbuf();   
  vertexShaderFile.close();
  shaderString = vertexShaderData.str(); 
  shaderText = shaderString.c_str();     
  textLength = (GLint)shaderString.size();
  Data::OB() << "Compiling fragment shader..." << std::endl;
  GLuint virt = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(virt, 1, &shaderText, &textLength);
  glCompileShader(virt);
  Data::OB() << "Vertex shader compiled successfully" << std::endl;

  // link shader program
  Data::OB() << "Linking shaders..." << std::endl;
  program = glCreateProgram();
  glAttachShader(program, frag);
  glAttachShader(program, virt);
  glLinkProgram(program);
  glUseProgram(program);
  Data::OB() << "Shaders linked successfully" << std::endl;
}

Compiler::~Compiler() {
  GLuint shaders[2];
  GLsizei count;
  glGetAttachedShaders(m_program, 2, &count, shaders);
  for (int i = 0; i < count; ++i)
    glDeleteShader(shaders[i]);
  glDeleteProgram(m_program);
}
