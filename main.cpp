#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "nlohmann_json/include/nlohmann/json.hpp"
#include <Windows.h>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;
using json = nlohmann::json;


struct Entry {
    size_t doc_id, count;

// Данный оператор необходим для проведения тестовых сценариев
    bool operator==(const Entry &other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
using IndexEntry = vector<Entry>;

class ConverterJSON {


private:
    string name_program;
    double number_of_verson;
    int max_responses;
    map<string, string> text_file;
    vector<string> path_file;
    vector<string> requests;
    vector<vector<string>> requestWords;
    vector<vector<string>> textWords;
    vector<string> searchWords;
    json answers_dict;


public:
    ConverterJSON() = default;

// методо открывает файл config.json считывает данные в созданные переменные
    void get_path() {
        ifstream file_config_read("config.json");
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
    }

// метод открывает файл с запросами и сохраняет их.
    void GetRequests() {
        ifstream file_requests_read("requests.json");
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
    map<string, string> GetTextDocuments() {

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


//Функция для замены символов переноса сторики
    static string removeLineBreaks(const string &input_string) {
        string result = input_string; // Create a copy of the input string

        // Remove carriage returns ('\r') and newlines ('\n')
        replace(result.begin(), result.end(), '\r', ' ');
        replace(result.begin(), result.end(), '\n', ' ');

        return result;
    };
};


// метод нахождения соответсвий.
//    void find_request() {
//
//
//        //  Предобработка requests: переводим в нижний регистр и разбиваем на слова
//
//        for (string &request: requests) {
//            request = toLower(request);
//            requestWords.push_back(splitString(request));
//        }
//
//        string line;
//        int count;
//        int _ = 5;
//        map<int, int> mymap;
//
//        for (const auto &n: path_file) {
//
//            count = 0;
//
//            std::stringstream buffer;
//            text_file.clear();
//            ifstream file_read(n);
//            if (file_read.is_open()) {
//                buffer << file_read.rdbuf();
//                file_read.close();
//                string lowerText = toLower(removeLineBreaks(buffer.str()));
//                searchWords = splitString(lowerText);
//            };
//
//
//            mymap.clear();
//
//
//            for (int j{0}; j < requests.size(); j++) {
//                count = 0;
//
//                for (const string &searchWord: searchWords) {
//                    for (size_t x = 0; x < requestWords[j].size(); ++x) {
//                        if (requestWords[j][x] == searchWord) {
//                            count++;
//                        }
//                    }
//                }
//                mymap[j + 1] = +count;
//            }
//            for (const auto &[product, price]: mymap)
//                std::cout << product << "\t" << price << std::endl;
//            cout << "\n";
//        }
//    }
//};

class InvertedIndex {
public:
    InvertedIndex() = default;

    // Функция для преобразования строки в нижний регистр
    static std::string toLower(const std::string &str) {

        std::string result = str; // Создаем копию строки, чтобы не изменять исходную
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }


// Функция для разбиения строки на слова
    static vector<string> splitString(const string &str) {
        vector<string> words;
        stringstream ss(str);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    };

    void UpdateDocumentBase(const map<string, string>& input_docs) {

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
    }


    void show() {
        for (const auto &entry: freq_dictionary) {
            cout << "index[\"" << entry.first << "\"] = ";
            for (size_t i = 0; i < entry.second.size(); ++i) {
                cout << "{" << entry.second[i].doc_id << ", " << entry.second[i].count << "}";
                if (i < entry.second.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

//    std::vector<Entry> GetWordCount(const std::string& word){
//
//    };
private:
    size_t doc_id = 0;
    string lowerText;
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный
//    словарь
};


    int main() {

        SetConsoleOutputCP(CP_UTF8);
        InvertedIndex gal;
        ConverterJSON file_request;
        file_request.get_path();
        file_request.GetRequests();
        gal.UpdateDocumentBase(file_request.GetTextDocuments());
        gal.show();

         
//    file_request.find_request();

//        for(auto alement:file_request.GetTextDocuments()){
//            cout<<alement.first<<"\n"<<alement.second<<"\n";
//        }

    }


