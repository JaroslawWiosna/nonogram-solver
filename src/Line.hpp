#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

struct Cell;

// this is a container of references: row or column
struct Line {
    std::vector<std::reference_wrapper<Cell>> line;
    std::reference_wrapper<Cell> operator[](size_t i);
};

char* pp(Line line);