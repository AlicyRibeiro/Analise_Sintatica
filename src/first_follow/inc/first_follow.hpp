#ifndef FIRST_H
#define FIRST_H

using namespace std;

#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

extern map<string, vector<vector<string>>> LR0;
extern map<string, set<string>> FIRST, FOLLOW;
extern string iniSimbol;

bool isTerminal(const string& simbol);
void Follow();
void First(const string& simbol);


#endif