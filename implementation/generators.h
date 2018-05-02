#pragma once

#include "common.h"

#include <functional>

void GenerateAll(int n, std::function<void(TAdjacencyMatrix&)> callback);
void GenerateRandom(int n, std::function<void(TAdjacencyMatrix&)> callback);
