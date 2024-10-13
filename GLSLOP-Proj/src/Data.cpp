//------------------------------------------------------------------------------
//
// File Name:	Data.cpp
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
#include "Data.h"

#include <sstream>
#include "nfd\nfd.h"

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

Dir& Data::operator[](std::size_t index) {
  return m_dir[index];
}

Dir Data::Folder() {
  return m_dir[FOLDER];
}

Dir Data::VertexShader() {
  return m_dir[VERT];
}

Dir Data::FragmentShader() {
  return m_dir[FRAG];
}

std::pair<std::string, bool> Data::OpenFolderDialog(std::ostringstream& os) {
  nfdchar_t* outPath = nullptr;
  nfdresult_t result = NFD_PickFolder(nullptr, &outPath);

  if (result == NFD_OKAY) {
	os << "Selected folder: " << outPath << std::endl;
	std::string folder(outPath);
	free(outPath); // Don't forget to free the allocated string
	return std::make_pair(folder, true);
  }
  else if (result == NFD_CANCEL) {
	os << "User canceled." << std::endl;
  }
  else {
	os << "Error: " << NFD_GetError() << std::endl;
  }
  return std::make_pair("None", false);
}

std::pair<std::string, bool> Data::OpenShader(ST shader, std::ostringstream& os) {
  nfdchar_t* outPath;
  const nfdchar_t* filters = { "vert glsl vs" };
  nfdresult_t result = NFD_OpenDialog(filters, nullptr, &outPath);

  if (result == NFD_OKAY) {
	os << "Selected File: " << outPath << std::endl;
	std::string file(outPath);
	free(outPath);
	return std::make_pair(file, true);
  }
  else if (result == NFD_CANCEL) {
	os << "User canceled." << std::endl;
  }
  else {
	os << "Error: " << NFD_GetError() << std::endl;
  }
  return std::make_pair("None", false);
}
