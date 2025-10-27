#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "map"
#include "static_metod.h"

using namespace std;
using json = nlohmann::json;
const std::string relative_path = "../../";
const std::string relative_path_answers = relative_path + "json_file/answers.json";

class ConverterJSON {

private:
    string name_program;
    int number_of_verson;
    int max_responses;
    vector<string> text_file;
//    vector<vector<RelativeIndex>> searchResults;
    vector<string> path_file;
    vector<string> requests;
    vector<vector<string>> requestWords;

public:

    void get_path();

    vector <string> GetRequests();

    vector <string> GetTextDocuments();

    int GetResponsesLimit() const;
    int Getnameversion() const;

    void request_apdeit();

    void find_request(const map<string, vector<Entry>> &base);

    void printResults(vector<vector<RelativeIndex>> searchResults) const;
};