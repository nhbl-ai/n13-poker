#pragma once
#include <iostream>

using namespace std;

struct Card {
    int rank; 
    char suit;

    Card(const int& s, const char& r) : rank(s), suit(r) {}
};
