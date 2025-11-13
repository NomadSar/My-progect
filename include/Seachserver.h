#pragma once

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include "coverter.h"
#include "inverted_index.h"
#include "static_metod.h"



/*! \class SearchServer */
/*! \brief Класс позволяет определять наиболее релевантные, соответствующие поисковому запросу, документы по прочитанным из файла requests.json поисковым запросам */
class SearchServer {
public:
    /*! \brief Конструктор */
    /*! \param idx ссылка на класс InvertedIndex, чтобы SearchServer мог узнать частоту слов встречаемых в запросе */
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    /*! \brief Метод обработки поисковых запросов */
    /*! \param queries_input поисковые запросы, взятые из файла requests.json */
    /*! \returns Возвращает отсортированный список релевантных ответов для заданных запросов */
    std::vector<std::vector<RelativeIndex>> search( const std::vector<std::string>& queries_input);
private:
    InvertedIndex _index;
};
