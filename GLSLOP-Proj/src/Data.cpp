﻿//------------------------------------------------------------------------------
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
