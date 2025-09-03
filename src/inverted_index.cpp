#include "inverted_index.h"
#include "static_metod.h"

// Заполнение базы данных
    map<std::string, std::vector<Entry>> InvertedIndex::UpdateDocumentBase(const map<string, string>& input_docs) {

        for (const auto& [name_path, text] : input_docs) {
            // Avoid re-processing existing documents (if desired)
             if (freq_dictionary.count(name_path)) continue;

             lowerText = toLower(text);
             docs = splitString(lowerText);

            for (const string& searchWord : docs) {
                auto it = freq_dictionary.find(searchWord);

                if (it != freq_dictionary.end()) {
                    // Word exists, check if an entry for this document exists
                    bool found = false;
                    for (auto& entry : it->second) {
                        if (entry.doc_id == doc_id) {
                            entry.count++;
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        it->second.push_back({doc_id, 1});
                    }
                } else {
                    // Word doesn't exist, create a new entry
                    freq_dictionary[searchWord] = {{doc_id, 1}};
                }
            }
            doc_id++; // Increment the document index for the next document
        }
        return freq_dictionary;
    }
