#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

enum class Cell_type {
    unfilled = -1,
    empty,
    one,
};

struct Cell {
    Cell_type type = Cell_type::unfilled;
    void print() const {
        switch (type) {
            case Cell_type::unfilled: {
                std::cout << "-";
                return;
            }
            case Cell_type::empty: {
                std::cout << "x";
                return;
            }
            case Cell_type::one: {
                std::cout << "1";
                return;
            }
        }
    }
};
