#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "map"
#include "static_metod.h"
using namespace std;
using json = nlohmann::json;

class ConverterJSON {

private:
    string name_program;
    double number_of_verson;
    int max_responses;
    map<string, string> text_file;
    vector<vector<RelativeIndex>> searchResults;
    vector<string> path_file;
    vector<string> requests;
    vector<vector<string>> requestWords;

public:

    void get_path() ;

    void GetRequests() ;

    map<string, string> GetTextDocuments() ;

    void request_apdeit();

    void find_request(const map<string, vector<Entry>> &base) ;

};