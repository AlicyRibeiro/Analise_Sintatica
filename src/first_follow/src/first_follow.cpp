#include "first_follow.hpp"

map<string, vector<vector<string>>> LR0;
map<string, vector<vector<string>>> gram;
map<string, set<string>> FIRST, FOLLOW;
string iniSimbol = "S";
// quebra em símbolos ("L , S" → ["L", ",", "S"])
vector<string> split(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string token;
    while (ss >> token)
        result.push_back(token);
    return result;
}

bool isTerminal(const string& simbol) {
    return !(isupper(simbol[0]) || simbol == "S'");
}