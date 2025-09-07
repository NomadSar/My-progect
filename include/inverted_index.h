#pragma once

#include "static_metod.h"

class InvertedIndex {
public:

    map<std::string, std::vector<Entry>> UpdateDocumentBase(const map<string, string> &input_docs);

private:
    size_t doc_id = 0;
    string lowerText;
    vector<string> docs; // список содержимого документов
    map<string, vector<Entry>> freq_dictionary; // частотный словарь
};