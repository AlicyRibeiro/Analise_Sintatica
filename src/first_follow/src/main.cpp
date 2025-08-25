#include "first_follow.hpp"

int main() {
    // gratica lr(0) do exemplo
    LR0["S'"] = { {"S"} };
    LR0["S"] = { {"(", "L", ")"}, {"x"} };
    LR0["L"] = { {"S"}, {"L", ",", "S"} };
    
    for (auto it = LR0.begin(); it != LR0.end(); ++it) {
        First(it->first);
    }    

    cout << "FIRST:\n";
    for (auto it = FIRST.begin(); it != FIRST.end(); ++it) {
        auto& n_terminal = it->first;
        auto& simbols = it->second;
    
        cout << n_terminal << ": { ";
        for (auto i = simbols.begin(); i != simbols.end(); ++i) {
            cout << *i << " ";
        }
        cout << "}\n";
    }

    Follow();
    cout << "FOLLOW:\n";
    for (auto it = FOLLOW.begin(); it != FOLLOW.end(); ++it) {
        auto& n_terminal = it->first;
        auto& simbols = it->second;
    
        cout << n_terminal << ": { ";
        for (auto i = simbols.begin(); i != simbols.end(); ++i) {
            cout << *i << " ";
        }
        cout << "}\n";
    }

    return 0;
}
