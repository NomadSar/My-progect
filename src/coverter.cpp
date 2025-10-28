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


int ConverterJSON::GetResponsesLimit() {
    ifstream file_config_read("..\\json_file\\config.json");
    if (file_config_read.is_open()) {
        json config_dict;
        file_config_read >> config_dict;

        max_responses = config_dict["config"].value("max_responses", 5);
    }else {
        cerr<<"dont have max_responses";
    }
    return max_responses;

}
int ConverterJSON::Get_number_version() {
    ifstream file_config_read("..\\json_file\\config.json");
    if (file_config_read.is_open()) {
        json config_dict;
        file_config_read >> config_dict;

        number_of_verson = config_dict["config"].value("version", 1);
    }else {
        cerr<<"dont have name program";
    }
    return number_of_verson;

}

string ConverterJSON::GetEngineName() {
    ifstream file_config_read("..\\json_file\\config.json");
    if (file_config_read.is_open()) {
        json config_dict;
        file_config_read >> config_dict;

        name_program = config_dict["config"].value("name", "UnknownEngine");
    }else {
        cerr<<"dont have name program";
    }
    return name_program;

}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    std::ofstream answers_file;
    nlohmann::json answers_data;
    nlohmann::json requests;
    nlohmann::json rel;

        answers_file.open("..\\json_file\\answers.json");

        for (size_t i = 0; i < answers.size(); i++)
        {
            std::vector<nlohmann::json> relevance;
            nlohmann::json request;
            if (answers[i].size() > 1)
            {
                request["result"] = "true";
                for (auto & j : answers[i])
                {
                    rel["docid"] = j.first;
                    rel["rank"] = j.second;
                    relevance.emplace_back(rel);
                }
                request["relevance"] = relevance;
            }
            else if (answers[i].size() == 1)
            {
                request["result"] = "true";
                request["docid"] = answers[i][0].first;
                request["rank"] = answers[i][0].second;
            }
            else
            {
                request["result"] = "false";
            }
            requests["request" + std::string(i + 1 < 10 ? "00" : (i + 1 < 100 ? "0" : "")) + std::to_string(i + 1)] = request;
        }
        answers_data["answers"] = requests;
        answers_file << std::setw(4) << answers_data << std::endl;
        answers_file.close();

}


