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

Compiler::Compiler(Dir fragDir, Dir virtDir)
: m_program(0) {
  GLint value;

  Data::OB() << "Reading fragment file..." << std::endl;
  GLuint& program = m_program;
  std::ifstream fragmentShaderFile(fragDir.first.c_str());
  std::stringstream fragmentShaderData;
  fragmentShaderData << fragmentShaderFile.rdbuf();
  fragmentShaderFile.close();
  std::string shaderString = fragmentShaderData.str();
  const char* shaderText = shaderString.c_str();
  GLint textLength = (GLint)shaderString.size();
  Data::OB() << "Compiling fragment shader..." << std::endl;
  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &shaderText, &textLength);
  // glSlopParse(frag);
  glCompileShader(frag);
  glGetShaderiv(frag, GL_COMPILE_STATUS, &value);
  if (!value) {
    char buffer[1024];
    glGetShaderInfoLog(frag, 1024, 0, buffer);
    Data::OB() << "Fragment shader could not compile:" << std::endl;
    Data::OB() << buffer << std::endl;
  }
  else {
    Data::OB() << "Fragment shader compiled successfully" << std::endl;
  }

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
  // glSlopParse(virt);
  glCompileShader(virt);
  glGetShaderiv(virt, GL_COMPILE_STATUS, &value);
  if (!value) {
    char buffer[1024];
    glGetShaderInfoLog(virt, 1024, 0, buffer);
    Data::OB() << "Vertex shader could not compile:" << std::endl;
    Data::OB() << buffer << std::endl;
  }
  else {
    Data::OB() << "Vertex shader compiled successfully" << std::endl;
  }

  // link shader program
  Data::OB() << "Linking shaders..." << std::endl;
  program = glCreateProgram();
  glAttachShader(program, frag);
  glAttachShader(program, virt);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &value);
  if (!value) {
    Data::OB() << "shader program failed to link" << std::endl;
    char buffer[1024];
    glGetProgramInfoLog(program, 1024, 0, buffer);
    Data::OB() << buffer << std::endl;
  }
  else {
    Data::OB() << "Shaders linked successfully" << std::endl;
  }
}

Compiler::~Compiler() {
  GLuint shaders[2];
  GLsizei count;
  glGetAttachedShaders(m_program, 2, &count, shaders);
  for (int i = 0; i < count; ++i)
    glDeleteShader(shaders[i]);
  glDeleteProgram(m_program);
}
