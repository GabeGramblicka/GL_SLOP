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

std::string GetNewFile(const char* path) {
  std::ifstream includeFile(path);
  std::stringstream includeData;
  includeData << includeFile.rdbuf();
  includeFile.close();

  return includeData.str();
}

std::string GetPath(const char* shaderText, size_t begin, size_t& end) {
  std::string sText = shaderText;
  size_t c = 0;
  const size_t quoteCount = 2;
  int quotes[2] = { 0 };

  int i; 
  for (i = 0; c < quoteCount; ++i) {
    if (sText[begin + i] == '"') {
      quotes[c] = begin + i;
      c++;
    }
  }

  end = quotes[1];
  std::string path = sText.substr(quotes[0] + 1, end - quotes[0] - 1);
  return path;
}

void glSlopParse(const char** shaderText, const char* includeShaderPath) {
  const char* includeString = "#include";
  size_t iSize = strlen(includeString) /* 8 */; // include length

  std::string sText = *shaderText;
  std::string path;

  size_t oSize = strlen(*shaderText);
  for (int i = 0; i < oSize; ++i) {
    Data::OB() << (*shaderText)[i];

    size_t beginFind = i;

    for (int j = 0; j < iSize; ++j) {
      if (j == iSize - 1) {
        std::cout << "Found include" << std::endl;
        size_t end;
        path = GetPath(*shaderText, beginFind, end);

        // Get substrings
        std::string s1 = sText.substr(0, beginFind);
        std::string s2 = sText.substr(end);

        // Find the file
        std::string root = includeShaderPath + path;
        std::string inc = GetNewFile(root.c_str());

        // Combine files
        std::string final = s1 + inc + s2;
        *shaderText = final.c_str();

        return;

      }
      if ((*shaderText)[i] != includeString[j]) {
        j = 0; // reset
        break;
      }
      else {
        Data::OB() << (*shaderText)[i];
        ++i;
      }
    }
  }
}


