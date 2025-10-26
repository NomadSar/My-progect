#pragma once

#include "static_metod.h"
#include <algorithm>
#include <sstream>
#include <thread>
#include <mutex>

class InvertedIndex {
public:
    /*! \brief Конструктор по умолчанию */
    InvertedIndex() = default;

    /*! \brief Метод для обновления или заполнения базы документов, по которой будет совершаться поиск */
    /*! \param input_docs содержимое документов */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /*! \brief Метод для определения количества вхождений слова word в загруженной базе документов */
    /*! \param word слово, частоту вхождений которого необходимо определить */
    /*! \returns Возвращает подготовленный список с частотой слов */
    std::vector<Entry> GetWordCount(const std::string& word);

    /*! \brief Метод для возвращения количества файлов */
    size_t GetFilesCount() const;

    std::map<std::string, std::vector<Entry>> get_dict();

private:
    /*! \brief Список содержимого документов */
    /*! \details Коллекция для хранения текстов документов, в которой номер элемента в векторе определяет doc_id для формирования результата запроса */
    std::vector<std::string> docs;

    /*! \brief Частотный словарь */
    /*! \details Коллекция для хранения частоты слов, встречаемых в тексте */
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    /*! \brief количество файлов */
    size_t files_count = 0;
};