#pragma once
#ifndef FILE_STUCTURE_ANALYZER_H
#define FILE_STRUTURE_ANALYZER_H
#include <string>

#include "../GameInstance.h"

// Takes a file input and creates all the things in the level from it
void analyzeFile(const std::string& source, GameInstance& instance);

#endif
