#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>
#include "nlohmann/json.hpp"

using namespace std;

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank > (other.rank - 0.000001) && rank < (other.rank + 0.000001));
    }
};

struct Entry {
    size_t doc_id, count;


    bool operator==(const Entry &other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

string toLower(const string &str);

vector<string> splitString(const string &str);

string removeLineBreaks(const string &input_string);

bool compareRelativeIndex(const RelativeIndex &a, const RelativeIndex &b);