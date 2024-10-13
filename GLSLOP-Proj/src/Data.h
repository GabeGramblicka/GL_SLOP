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

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <sstream>

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

using Dir = std::pair<std::string, bool>;

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Enums:
//------------------------------------------------------------------------------

enum { FOLDER = 0 }; // Will be index 0 of dir array
enum ShaderType {
  VERT = 1, // index 1 of dir array
  FRAG = 2  // index 2 of dir array
};
using ST = ShaderType;

//------------------------------------------------------------------------------
// Classes:
//------------------------------------------------------------------------------

class Data {
public:
  std::ostringstream& OB() { return m_outputBuffer; }

  Dir& operator[](std::size_t index);
  Dir Folder();
  Dir VertexShader();
  Dir FragmentShader();
  static std::pair<std::string, bool> OpenFolderDialog(std::ostringstream& os);
  static std::pair<std::string, bool> OpenShader(ST shader, std::ostringstream& os);
private:
  std::array<Dir, 3> m_dir = { std::make_pair("None", false) };
  std::ostringstream m_outputBuffer;
};