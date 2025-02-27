#pragma once
#include "matrix.h"
#include <random>
#include <vector>

Point GenerateRandomPoint(size_t max_dimension);


std::vector<Point> GenerateVectorOfRandPoints(size_t max_dimension, size_t max_count);