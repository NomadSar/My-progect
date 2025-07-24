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

class ConverterJSON {


private:
    string name_program;
    double number_of_verson;
    int max_responses;
    vector<string> text_file;
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
//    void GetTextDocuments() {
//        for (const auto &n: path_file) {
//            ifstream file_read(n);
//            if (file_read.is_open()) {
//                string line;
//                while (getline(file_read, line)) {
//                    text_file.push_back(line);
//                }
//                file_read.close();
//            }
//        }
//    };

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
    }
//Функция для замены символов переноса сторики
    static string removeLineBreaks(const string& input_string) {
        string result = input_string; // Create a copy of the input string

        // Remove carriage returns ('\r') and newlines ('\n')
        replace(result.begin(), result.end(), '\r', ' ');
        replace(result.begin(), result.end(), '\n', ' ');

        return result;
    }

// метод нахождения соответсвий.
    void find_request() {


        //  Предобработка requests: переводим в нижний регистр и разбиваем на слова

        for (string &request: requests) {
            request = toLower(request);
            requestWords.push_back(splitString(request));
        }

        string line;
        int count;
        int _ = 5;
        map<int, int> mymap;

        for (const auto &n: path_file) {

            count = 0;

            std::stringstream buffer;
            text_file.clear();
            ifstream file_read(n);
            if (file_read.is_open()) {
                buffer << file_read.rdbuf();
                file_read.close();
                string lowerText = toLower(removeLineBreaks(buffer.str()));
                searchWords = splitString(lowerText);
            };


            mymap.clear();


            for (int j{0}; j < requests.size(); j++) {
                count = 0;

                for (const string &searchWord: searchWords) {
                    for (size_t x = 0; x < requestWords[j].size(); ++x) {
                        if (requestWords[j][x] == searchWord) {
                            count++;
                        }
                    }
                }
                mymap[j + 1] = +count;
            }
            for (const auto &[product, price]: mymap)
                std::cout << product << "\t" << price << std::endl;
            cout << "\n";
        }
    }
};


int main() {

    SetConsoleOutputCP(CP_UTF8);

    ConverterJSON file_request;
    file_request.get_path();
    file_request.GetRequests();
//    file_request.GetTextDocuments();
    file_request.find_request();


}

//////  Цикл по text_file
//for (int i{0}; i < text_file.size(); i++) {
//string lowerText = toLower(text_file[i]);
//vector<string> searchWords = splitString(lowerText);
//int number = max_responses;
//// 3. Цикл по requests
//for (int j{0}; j < requests.size(); j++) {
//int count = 0;
//
////  Поиск вхождений
//for (const string &searchWord: searchWords) {
//for (size_t x = 0; x < requestWords[j].size(); ++x) {
//if (requestWords[j][x] == searchWord) {
//count++;
//}
//}
//}

////  Вычисление rank (с проверкой деления на ноль и более понятной логикой)
//
//double rank = 0.0; // Default value
//if (count == 0) { // Avoid division by zero
//answers_dict["answers"]["request00" + to_string(j + 1)]["result"] = false;
//} else {
//rank = static_cast<double>(count) / static_cast<double>(requestWords[j].size());
//answers_dict["answers"]["request00" + to_string(j + 1)]["relevance"][i]["docid"] = i + 1;
//answers_dict["answers"]["request00" + to_string(j + 1)]["relevance"][i]["rank"] = rank;
//}
//
//
//
//}
//}
//std::cout << std::setw(4) << answers_dict << std::endl;
//// запись в файл.
//std::ofstream outputFile("answers.json");
//outputFile << std::setw(4) << answers_dict << std::endl;
//
//
//outputFile.close();
