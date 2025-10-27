#include "inverted_index.h"
#include "static_metod.h"

// Заполнение базы данных
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    static std::mutex freq_dictionary_mutex; // статический мьютекс для защиты общего словаря
    /* очистка имеющихся данных */
    docs.clear();
    freq_dictionary.clear();

    docs.resize(input_docs.size());
    files_count = input_docs.size();

    /* заполнение новыми данными файла docs */
    std::copy(input_docs.begin(), input_docs.end(), docs.begin());

    /* обработка документов */
    auto process_document = [&](size_t i) {
        std::stringstream buffer_stream(input_docs[i]);
        std::string word;
        int word_count = 0;
        while (buffer_stream >> word && word_count < 1000) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word.empty()) {
                break;
            } else if (word.size() > 100) {
                word.resize(100);
            }
            word_count++;

            // блокировка для доступа к freq_dictionary
            {
                std::lock_guard<std::mutex> lock(freq_dictionary_mutex);
                auto it = freq_dictionary.find(word);
                if (it != freq_dictionary.end()) {
                    bool flag = false;
                    for (auto& entry : it->second) {
                        if (entry.doc_id == i) {
                            entry.count++;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        it->second.emplace_back(Entry{.doc_id = i, .count = 1});
                    }
                } else {
                    freq_dictionary[word] = { Entry{.doc_id = i, .count = 1} };
                }
            }
        }
    };

    // Можно запустить обработку в параллели, если нужно
    // Например, с помощью std::thread или std::async
    for (size_t i = 0; i < input_docs.size(); ++i) {
        process_document(i);
    }
}



std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    if (freq_dictionary.find(word) != freq_dictionary.end())
    {
        return freq_dictionary[word];
    }

    return std::vector<Entry>(0);
}

size_t InvertedIndex::GetFilesCount() const
{
    return files_count;
}


