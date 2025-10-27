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
        number_of_verson = config_dict["config"].value("version", 1);
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
vector <string> ConverterJSON::GetRequests() {
    ifstream file_requests_read("..\\json_file\\requests.json");
    if (file_requests_read.is_open()) {
        json requests_dict;
        file_requests_read >> requests_dict;
        int i{0};
        for (auto iterator_first = requests_dict.begin();
             iterator_first != requests_dict.end(); ++iterator_first) {
            for (auto iterator_sekond = iterator_first.value().begin();
                 iterator_sekond != iterator_first.value().end() && i < max_responses; ++iterator_sekond, i++) {
                requests.push_back(to_string(iterator_sekond.value()));
            }
        }
    } else {
        cerr << "requests file is missing" << endl;
    }
    file_requests_read.close();
    return requests;
}


/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
vector<string> ConverterJSON::GetTextDocuments() {

    for (const auto &item: path_file) {
        ifstream file_read(item);
        if (file_read.is_open()) {
            std::stringstream buffer;
            buffer << file_read.rdbuf();
            text_file.push_back(removeLineBreaks(buffer.str())) ;

            file_read.close();
            buffer.clear();
        }
    }
    return text_file;
}

//Перевод текста запроса в нижний регист и формирование вектора из разбитых слов
//void ConverterJSON::request_apdeit() {
//    for (string &request: requests) {
//        request = toLower(request);
//        requestWords.push_back(splitString(request));
//    }
//};

void ConverterJSON::printResults(vector<vector<RelativeIndex>> searchResults) const  {
    json answers_dict;
    answers_dict["answers"]["number_of_verson"] = Getnameversion();
    cout<<Getnameversion();
    for (size_t i = 0; i < searchResults.size(); ++i) {
        string request_num = "request00" + to_string(i + 1);
        if (searchResults[i].empty()) {
            answers_dict["answers"][request_num]["result"] = false;
        } else {
            answers_dict["answers"][request_num]["result"] = true;
            json relevance_array;
            for (const auto &result: searchResults[i]) {
                json doc_info;
                doc_info["docid"] = result.doc_id;
                doc_info["rank"] = result.rank;
                relevance_array.push_back(doc_info); // Append each document
            }
            answers_dict["answers"][request_num]["relevance"] = relevance_array;
        }
    }
    std::ofstream outputFile("..\\json_file\\answers.json");
    outputFile << std::setw(4) << answers_dict << std::endl;
    outputFile.close();
}

int ConverterJSON::GetResponsesLimit() const{
    return max_responses;
}

int ConverterJSON::Getnameversion() const{
    return number_of_verson;
}



