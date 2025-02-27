#include "combinatorics.h"


Point GenerateRandomPoint(size_t max_dimension){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, max_dimension - 1);
    size_t x, y = 0;
    x = distrib(gen);
    y = distrib(gen);
    return {x, y};
}


std::vector<Point> GenerateVectorOfRandPoints(size_t max_dimension, size_t max_count){

    std::vector<Point> result(max_count);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distrib(0, max_dimension - 1);


    for (size_t i = 0; i < max_count; ++i){
        size_t x, y = 0;
        x = distrib(gen);
        y = distrib(gen);
        result[i] = {x, y};
    }

    return result;
}