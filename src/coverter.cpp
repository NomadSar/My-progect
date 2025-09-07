#include "coverter.h"
#include "static_metod.h"

// метод открывает файл config.json считывает данные в созданные переменные
void ConverterJSON::get_path() {
    ifstream file_config_read("..\\json_file\\config.json");
    if (file_config_read.is_open()) {
        string target = "config";
        json config_dict;
        file_config_read >> config_dict;
        if (config_dict.find(target) == config_dict.end()) {
            cerr << "config file is empty" << endl;
        }

        name_program = config_dict["config"].value("name", "UnknownEngine");
        number_of_verson = config_dict["config"].value("version", 0.1);
        max_responses = config_dict["config"].value("max_responses", 5);

        for (auto iterator_first = config_dict.begin(); iterator_first != config_dict.end(); ++iterator_first) {
            for (auto iterator_sekond = iterator_first.value().begin();
                 iterator_sekond != iterator_first.value().end(); ++iterator_sekond) {
                if (iterator_first.key() == "files") {
                    path_file.push_back(iterator_sekond.value());
                }
            }
        }
        file_config_read.close();
    } else {
        cerr << "config file is missing" << endl;
    }
};

// метод открывает файл с запросами и сохраняет их.
void ConverterJSON::GetRequests() {
    ifstream file_requests_read("..\\json_file\\requests.json");
    if (file_requests_read.is_open()) {
        json requests_dict;
        file_requests_read >> requests_dict;
        int i{0};
        for (auto iterator_first = requests_dict.begin();
             iterator_first != requests_dict.end(); ++iterator_first) {
            for (auto iterator_sekond = iterator_first.value().begin();
                 iterator_sekond != iterator_first.value().end() && i < max_responses; ++iterator_sekond, i++) {
                requests.push_back(iterator_sekond.value());
            }
        }
    } else {
        cerr << "requests file is missing" << endl;
    }
    file_requests_read.close();
};


/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
map<string, string> ConverterJSON::GetTextDocuments() {

    for (const auto &path_file: path_file) {
        ifstream file_read(path_file);
        if (file_read.is_open()) {
            std::stringstream buffer;
            if (!text_file.count(path_file)) {
                buffer << file_read.rdbuf();
                text_file[path_file] = removeLineBreaks(buffer.str());
            }
            file_read.close();
            buffer.clear();
        }
    }
    return text_file;
};

//Перевод текста запроса в нижний регист и формирование вектора из разбитых слов
void ConverterJSON::request_apdeit() {
    for (string &request: requests) {
        request = toLower(request);
        requestWords.push_back(splitString(request));
    }
};


// Формирования итога запроса;
void ConverterJSON::find_request(const map<string, vector<Entry>> &base) {
    for (const auto &request_group: requestWords) {
        vector<RelativeIndex> current_group_results;
        size_t total_words_in_request = request_group.size();
        if (total_words_in_request == 0) {
            searchResults.push_back(current_group_results);
            continue;
        }

        map<size_t, size_t> doc_id_counts;
        for (const string &word: request_group) {
            auto it = base.find(word);
            if (it != base.end()) {
                for (const Entry &entry: it->second) {
                    doc_id_counts[entry.doc_id] += entry.count;
                }
            }
        }


        for (const auto &[doc_id, count]: doc_id_counts) {
            float rank = static_cast<float>(count) / static_cast<float>(total_words_in_request);


            rank = min(rank, 1.0f);

            RelativeIndex relative_index;
            relative_index.doc_id = doc_id;
            relative_index.rank = rank;
            current_group_results.push_back(relative_index);
        }

        sort(current_group_results.begin(), current_group_results.end(), compareRelativeIndex);
        searchResults.push_back(current_group_results); // Add the results for this group
    }
};






