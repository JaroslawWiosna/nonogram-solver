#include "Nonogram.hpp"
#include "Cell.hpp"
#include "Clue.hpp"
#include "Line.hpp"

#include <map>

Line Nonogram::get_row(size_t no) {
    static std::map<size_t, Line> cache;
    if (cache.find(no) == cache.end()) {
        Line result;
        for (size_t i{}; i < rows_count; ++i) {
            result.line.push_back(
                std::reference_wrapper<Cell>(mat.grid[no * cols_count + i]));
        }
        cache[no] = result;
    }
    return cache[no];
}

Line Nonogram::get_col(size_t no) {
    Line result;
    for (size_t i{}; i < rows_count; ++i) {
        result.line.push_back(
            std::reference_wrapper<Cell>(mat.grid[no + cols_count * i]));
    }
    return result;
}

void Nonogram::print() const {
    for (size_t i{}; i < cols_count + 2; ++i) {
        std::cout << '_';
    }
    std::cout << "\n";
    for (size_t x{}; x < rows_count; ++x) {
        std::cout << '|';
        for (size_t y{}; y < cols_count; ++y) {
            mat.grid[x * cols_count + y].print();
        }
        std::cout << '|';
        std::cout << "\n";
    }
}

Clue_line signature(std::vector<Cell> line) {
    Clue_line result = {};
    int cnt{};
    auto push_if_not_empty = [&result, &cnt]() {
        if (cnt != 0) {
            result.add(cnt);
            cnt = 0;
        }
    };
    for (const auto& item : line) {
        if (item.type == Cell_type::empty) {
            if (cnt != 0) {
                result.add(cnt);
                cnt = 0;
            }
        } else if (item.type == Cell_type::one) {
            ++cnt;
        } else {
            assert(!"This should never happened");
        }
    }
    if (cnt != 0) {
        result.add(cnt);
        cnt = 0;
    }
    return result;
}

std::vector<std::vector<Cell>> Nonogram::all_possibilities(size_t size) {
    assert(size > 0);
    std::vector<std::vector<Cell>> result;
    if (size == 1) {
        result.push_back({{Cell_type::empty}});
        result.push_back({{Cell_type::one}});
        return result;
    } else {
        std::vector<std::vector<Cell>> prev = all_possibilities(size - 1);
        for (const auto& item : prev) {
            auto x = item;
            auto o = item;
            x.push_back({Cell_type::empty});
            o.push_back({Cell_type::one});
            result.push_back(x);
            result.push_back(o);
        }
        return result;
    }
}

std::vector<std::vector<Cell>>
Nonogram::all_possibilities(size_t size, Clue_line clue_line) {
    auto all = all_possibilities(size);
    std::vector<std::vector<Cell>> result;
    for (const auto& item : all) {
        if (clue_line == signature(item)) {
            result.push_back(item);
        }
    }
    return result;
}

bool contradict(Line a, std::vector<Cell> b, Clue_line clue_line) {
    // line a: ---1--1--
    // vec  b: --1---1--
    // should return

    for (size_t i{}; i < b.size(); ++i) {
        if (b[i].type == Cell_type::unfilled &&
            a[i].get().type == Cell_type::unfilled) {
            continue;
        }
        if (b[i].type == Cell_type::unfilled) {
            b[i].type = a[i].get().type;
        }
    }

    return !(signature(b) == clue_line);
}

std::vector<std::vector<Cell>>
Nonogram::all_possibilities(size_t size, Clue_line clue_line, Line line) {
    auto all = all_possibilities(size, clue_line);
    std::vector<std::vector<Cell>> result;
    for (const auto& item : all) {
        if (!contradict(line, item, clue_line)) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<Cell> line_solution(std::vector<std::vector<Cell>> lines) {
    assert(lines.size() > 0);
    std::vector<Cell> result = lines[0];
    for (const auto& item : lines) {
        for (size_t i{}; i < result.size(); ++i) {
            if (result[i].type != item[i].type) {
                result[i].type = Cell_type::unfilled;
            }
        }
    }
    return result;
}

// xx1xx111xx11x
std::vector<int> find_seq_in_line(Line line, int seq) {
    std::vector<int> result;
    std::map<int, int> m;
    int tmp = 0;
    for (size_t i{}; i<line.line.size(); ++i) {
        if (line[i].get().type == Cell_type::one) {
            ++tmp;
        } else {
            if (tmp !=0) {
                m[i - tmp + 1] = tmp;
            }
            tmp = 0;
        }
    }
    for (const auto& [key, value] : m) {
        if (value == seq) {
            result.push_back(key);
        }
    }
    return result;;
}

void surrond_max_with_empty(Line line, Clue_line& row_clue, bool debug = false) {
    const int size = line.line.size();
    const int max_val_in_clue = row_clue.max_valid();
    auto indexes = find_seq_in_line(line, max_val_in_clue);
    if (0 == indexes.size()) {
        return;
    }
    for (int index : indexes) {
        if (debug) {
            std::cout << "debug\n";
        }
        row_clue.decrement_in_histogram(max_val_in_clue);
        int left = index - 1 - 1;
        int right = index + max_val_in_clue - 1;

        if (left >= 0) {
            line[left].get().type = Cell_type::empty;
        }

        if (right < size) {
            line[right].get().type = Cell_type::empty;
        }
    }
}

void Nonogram::solve() {
    int x = 1;
    while (x-- > 0) {
        std::cout << x << "\n";

        for (size_t i{}; i < rows_count; ++i) {
            auto line = get_row(i);
            auto& row_clue = rows_clues[i];
            auto all = all_possibilities(cols_count, row_clue, line);
            auto solution = line_solution(all);
            for (size_t i{}; i < solution.size(); ++i) {
                if (solution[i].type != Cell_type::unfilled) {
                    line[i].get() = solution[i];
                }
            }
            if (i == 6 && x < 9 && x > 5) {
                std::cout << "i == " << i << "\n";
            }
            surrond_max_with_empty(line, row_clue, i == 6);
            print();
        }
        for (size_t i{}; i < cols_count; ++i) {
            auto line = get_col(i);
            auto col_clue = cols_clues[i];
            auto all = all_possibilities(rows_count, col_clue);
            auto solution = line_solution(all);
            for (size_t i{}; i < solution.size(); ++i) {
                if (solution[i].type != Cell_type::unfilled) {
                    line[i].get() = solution[i];
                }
            }
                        surrond_max_with_empty(line, col_clue);

            print();
        }
    }
}
