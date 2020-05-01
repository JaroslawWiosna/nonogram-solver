#pragma once

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

struct Clue {
    int val = 0;
    bool expired = false;
    // Clue() : val{0}, expired{false} {}
    // Clue(int v) : val{v}, expired{false} {}
};

struct Clue_line {
    static const long unsigned int ARRAY_CAP = 20UL;
    std::array<Clue, ARRAY_CAP> arr{};
    size_t size = 0;
    std::map<int, int> histogram;
    Clue_line() {
    }
    Clue_line(std::initializer_list<int> l) {
        assert(l.size() <= ARRAY_CAP);
        for (const auto& i : l) {
            arr[size++] = Clue{i};
        }
        update_histogram();
    }
    void add(int val);
    // Clue_line& operator=(std::initializer_list<int> rhs) {
    //     size = 0;
    //     for (const auto & i : rhs) {
    //         arr[size++] = Clue{i};
    //     }
    //     return *this;
    // }
    void update_histogram();
    void decrement_in_histogram(int val);
    int max() const;
    int max_valid() const;
    Clue operator[](size_t i) const;
    bool operator==(const Clue_line& rhs) const;
};
