#include "Seachserver.h"
#include "static_metod.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search( const std::vector<std::string>& queries_input) {
    ConverterJSON converter;
    vector<vector<string>> requestWords;
    vector<vector<RelativeIndex>> searchResults;
    std::map<std::string, std::vector<Entry>> freq_dictionary = _index.get_dict();

    for (string request: queries_input) {
        std::string toRemove = "\"";

        std::size_t pos;
        while ((pos = request.find(toRemove)) != std::string::npos) {
            request.erase(pos, toRemove.size());
        }
        request = toLower(request);
        requestWords.push_back(splitString(request));
    }

    for (const auto &request_group: requestWords) {
        vector<RelativeIndex> current_group_results;
        size_t total_words_in_request = request_group.size();
        if (total_words_in_request == 0) {
            searchResults.push_back(current_group_results);
            continue;
        }

        map<size_t, size_t> doc_id_counts;
        for (const string &word: request_group) {
            auto it = freq_dictionary.find(word);
            if (it != freq_dictionary.end()) {
                for (const Entry &entry: it->second) {
                    doc_id_counts[entry.doc_id] += entry.count;
                }
            }
        }

        for (const auto &[doc_id, count]: doc_id_counts) {
            float rank = static_cast<float>(count) / static_cast<float>(total_words_in_request);


            rank = min(rank, 1.0f);

            RelativeIndex relative_index{};
            relative_index.doc_id = doc_id;
            relative_index.rank = rank;
            current_group_results.push_back(relative_index);
        }

        sort(current_group_results.begin(), current_group_results.end(), compareRelativeIndex);
        searchResults.push_back(current_group_results); // Add the results for this group
    }
    converter.printResults(searchResults);

    return searchResults;
}