#include "Clue.hpp"

Clue Clue_line::operator[](size_t i) const {
    if (i >= size) {
        throw std::out_of_range("array cap is .. , but the size is ...");
    }
    return arr[i];
}

void Clue_line::add(int val) {
    assert(size < ARRAY_CAP);
    arr[size++] = Clue{val};
    histogram[val]++;
}

void Clue_line::update_histogram() {
    for (size_t i{}; i < size; ++i) {
        histogram[arr[i].val]++;
    }
}

void Clue_line::decrement_in_histogram(int val) {
    histogram[val]--;
}


int Clue_line::max() const {
    int result{};
    for (size_t i{}; i < size; ++i) {
        if (arr[i].val > result) {
            result = arr[i].val;
        }
    }
    return result;
}

int Clue_line::max_valid() const {
    int result{};
    // for (size_t i{}; i < size; ++i) {
    //     if (arr[i].expired) {
    //         continue;
    //     }
    //     if (arr[i].val > result) {
    //         result = arr[i].val;
    //     }
    // }
    for (const auto [key, value] : histogram) {
        if (value > 0 && key > result) {
            result = key;
        }        
    }
    return result;
}

bool Clue_line::operator==(const Clue_line& rhs) const {
    if (size != rhs.size) {
        return false;
    }
    for (size_t i{}; i < size; ++i) {
        if (arr[i].val != rhs.arr[i].val) {
            return false;
        }
    }
    return true;
}