#include "Line.hpp"
#include "Cell.hpp"

std::reference_wrapper<Cell> Line::operator[](size_t i) {
    return line[i];
}

char* pp(Line line) {
    char* str = new char[30];
    int pos{};
    for (const auto& i : line.line) {
        char tmp = '?';
        if (i.get().type == Cell_type::unfilled) {
            tmp = '-';
        } else if (i.get().type == Cell_type::empty) {
            tmp = 'x';
        } else if (i.get().type == Cell_type::one) {
            tmp = '1';
        }
        str[pos++] = tmp;
    }
    return str;
}
