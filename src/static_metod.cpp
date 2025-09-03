#include "static_metod.h"

 std::string toLower(const std::string &str) {

    std::string result = str; // Создаем копию строки, чтобы не изменять исходную
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
};

 vector<string> splitString(const string &str) {
    vector<string> words;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
};

 string removeLineBreaks(const string &input_string) {
    string result = input_string; // Create a copy of the input string

    // Remove carriage returns ('\r') and newlines ('\n')
    replace(result.begin(), result.end(), '\r', ' ');
    replace(result.begin(), result.end(), '\n', ' ');

    return result;
};

bool compareRelativeIndex(const RelativeIndex& a, const RelativeIndex& b) {
    return a.rank > b.rank;
};