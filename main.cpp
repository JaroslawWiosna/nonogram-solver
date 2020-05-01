#include "Nonogram.hpp"

#include <functional>
#include <iostream>
#include <vector>

int main() {
    Nonogram n{5, 5};
    n.rows_clues[0] = {5};
    n.rows_clues[1] = {1, 3};
    n.rows_clues[2] = {1};
    n.rows_clues[3] = {1};
    n.rows_clues[4] = {1};

    n.cols_clues[0] = {5};
    n.cols_clues[1] = {1};
    n.cols_clues[2] = {2};
    n.cols_clues[3] = {2};
    n.cols_clues[4] = {2};

    // n[0][0].get() = {Cell_type::one};
    // n[3][1].get() = {Cell_type::one};

    n.print();
    n.solve();
    n.print();

    std::cout << "------------\n";

    Nonogram z{16, 16};
    z.rows_clues[0] = {3, 3, 3};
    z.rows_clues[1] = {2, 3, 3, 2};
    z.rows_clues[2] = {2, 4, 2};
    z.rows_clues[3] = {3, 1, 2, 3};
    z.rows_clues[4] = {2, 2, 2};
    z.rows_clues[5] = {1, 9, 1};
    z.rows_clues[6] = {
        1, 1, 1, 2, 1, 1, 1,
    };
    z.rows_clues[7] = {
        1, 1, 1, 2, 1, 1, 1,
    };
    z.rows_clues[8] = {
        1, 1, 1, 2, 1, 1, 1,
    };
    z.rows_clues[9] = {
        1, 1, 1, 2, 1, 1, 1,
    };
    z.rows_clues[10] = {1, 1, 4, 1, 1};
    z.rows_clues[11] = {1, 6, 1};
    z.rows_clues[12] = {1, 2, 3, 1};
    z.rows_clues[13] = {1, 2, 1, 2, 1};
    z.rows_clues[14] = {1, 3, 1};
    z.rows_clues[15] = {1, 1, 1};
    z.cols_clues[0] = {1, 2};
    z.cols_clues[1] = {4, 9};
    z.cols_clues[2] = {2, 2};
    z.cols_clues[3] = {1, 5, 1};
    z.cols_clues[4] = {1, 1, 2};
    z.cols_clues[5] = {1, 1, 5, 2};
    z.cols_clues[6] = {3, 1, 3, 1};
    z.cols_clues[7] = {1, 1, 8, 1};
    z.cols_clues[8] = {16};
    z.cols_clues[9] = {3, 1, 3, 1};
    z.cols_clues[10] = {1, 5, 2, 1};
    z.cols_clues[11] = {1, 2};
    z.cols_clues[12] = {7, 1};
    z.cols_clues[13] = {2, 2};
    z.cols_clues[14] = {4, 9};
    z.cols_clues[15] = {1, 2};

    z.solve();
    z.print();
}
