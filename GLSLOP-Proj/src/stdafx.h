//------------------------------------------------------------------------------
//
// File Name:	stdafx.h
// Author(s):	Gabe Gramblicka (gabriel.gramblicka)
// Project:		GL SLOP
//
// Copyright (c) 2024 Gabe Gramblicka
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Warnings
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Library Includes
//------------------------------------------------------------------------------

// #pragma warning(push, 0)

#define IMGUI_DEFINE_MATH_OPERATORS // For imgui.h
#include <imGui\imgui.h>
#include <imGui\imgui_stdlib.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// #pragma warning(pop)

//------------------------------------------------------------------------------
// Standard Library Includes
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iterator>

#define _USE_MATH_DEFINES // For math.h
#include <math.h>

#include <string>
#include <vector>
#include <array>