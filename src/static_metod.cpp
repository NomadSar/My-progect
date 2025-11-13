#include "static_metod.h"

string removeLineBreaks(const string &input_string) {
    string result = input_string;
    replace(result.begin(), result.end(), '\r', ' ');
    replace(result.begin(), result.end(), '\n', ' ');
    return result;
};

