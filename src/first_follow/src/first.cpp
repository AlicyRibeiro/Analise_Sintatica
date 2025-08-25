#include "first_follow.hpp"

void First(const string& simbol) {
    if (FIRST.count(simbol)) return;

    FIRST[simbol] = {};

    for (auto prod : LR0[simbol]) {
        string first = prod[0];

        if (isTerminal(first)) {
            FIRST[simbol].insert(first);
        } else {
            First(first);
            for (auto f : FIRST[first]) {
                if (f != "ε") FIRST[simbol].insert(f);
            }
        }
    }
}