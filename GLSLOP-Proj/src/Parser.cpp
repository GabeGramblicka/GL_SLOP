//------------------------------------------------------------------------------
//
// File Name:	Parser.c
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
#include "Parser.h"
#include "Data.h"

#include <stdio.h>

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

const char* GetPath(const char* shaderText, size_t begin, size_t end, size_t size) {
  char* s1 = (char*)calloc(1, begin);
  char* s2 = (char*)calloc(1, size - end);
  for (size_t i = 0; i < begin; ++i) {
    s1[i] = shaderText[i];
  }

  for (size_t i = end; i < size; ++i) {
    s2[i] = shaderText[i];
  }

  return nullptr;
}

const char* glSlopParse(const char* shaderText) {
  const char* includeString = "#include";
  size_t iSize = strlen(includeString) /* 8 */; // include length

  const char* includeFile = nullptr;
  const char* newFile = nullptr;

  size_t oSize = strlen(shaderText);
  for (int i = 0; i < oSize; ++i) {
    Data::OB() << shaderText[i];

    size_t beginFind = i;

    for (int j = 0; j < iSize; ++j) {
      if (j == iSize - 1) {
        std::cout << "Found include" << std::endl;
        const char* path = GetPath(shaderText, beginFind, i, oSize);
      }
      if (shaderText[i] != includeString[j]) {
        j = 0; // reset
        break;
      }
      else {
        Data::OB() << shaderText[i];
        ++i;
      }
    }
  }

  return newFile;
}


