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

void Data::ReadData() {
  std::ifstream file("files.dat");
  std::array<std::string, 3> text;

  int i = 0;
  while (i < 3 && getline(file, text[i])) {
	m_dir[i].first = text[i];
	if (text[i] == "" || text[i] == "None") {
	  m_dir[i].second = false;
	}
	else {
	  m_dir[i].second = true;
	}
	++i;
  }

  // Close the file
  file.close();
}

void Data::SaveData() {
  std::ofstream file("files.dat");

  // Write to the file
  file << m_dir[FOLDER].first << std::endl;
  file << m_dir[VERT].first << std::endl;
  file << m_dir[FRAG].first << std::endl;

  // Close the file
  file.close();
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
  const nfdchar_t* filters = nullptr;
  switch (shader) {
  case VERT:
	filters = { "vert,glsl,vs,txt" };
	break;
  case FRAG:
	filters = { "frag,glsl,fs,txt" };
	break;
  }
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
