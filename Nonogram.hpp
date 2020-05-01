#pragma once

#include "Cell.hpp"
#include "Clue.hpp"
#include "Line.hpp"
#include "Matrix.hpp"

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

struct Nonogram {
    static const long unsigned int MAX_COLS = 50UL;
    static const long unsigned int MAX_ROWS = 50UL;
    Matrix<Cell> mat;
    size_t cols_count;
    size_t rows_count;
    std::array<Clue_line, MAX_COLS> cols_clues{};
    std::array<Clue_line, MAX_COLS> rows_clues{};

    Nonogram(size_t x, size_t y) : cols_count{x}, rows_count{y} {
    }
    Line get_row(size_t i);
    Line get_col(size_t i);
    void print() const;
    Line operator[](size_t i) {
        return get_row(i);
    }
    std::vector<std::vector<Cell>> all_possibilities(size_t size);
    std::vector<std::vector<Cell>> all_possibilities(size_t size,
                                                     Clue_line clue_line);
    std::vector<std::vector<Cell>>
    all_possibilities(size_t size, Clue_line clue_line, Line line);
    void solve();
};