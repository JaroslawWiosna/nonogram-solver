#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <typename T> struct Matrix {
    static const long unsigned int ARRAY_CAP = 1000UL;
    std::array<T, ARRAY_CAP> grid;
};
