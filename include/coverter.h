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
    int number_of_verson;
    int max_responses;
    vector<string> text_file;
    vector<string> path_file;
    vector<string> requests;
    vector<vector<string>> requestWords;

public:

/*метод открывает файл config.json считывает данные в созданные переменные*/
    void get_path();
/*метод открывает файл с запросами и сохраняет их.*/
    vector <string> GetRequests();
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    vector <string> GetTextDocuments();
/* Считывает количество запросов*/
    int GetResponsesLimit() ;
/*Считывает номер версии программы*/
    int Get_number_version() ;
/* Считывает номер программы*/
    string GetEngineName() ;
/* Записывает итоговый результат в файл*/
    static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

};