#include "Seachserver.h"
#include "static_metod.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input)
{
    ConverterJSON converter;
    int response_limit = converter.GetResponsesLimit();

    /* отсортированный список релевантных ответов на запросы */
    std::vector<std::vector<RelativeIndex>> result;
    for (const auto & i : queries_input)
    {
        std::vector<RelativeIndex> result_inner;
        /* абсолютная релевантность каждому документу (внутр.v) */
        std::vector<size_t> absolute_relevance(_index.GetFilesCount(), 0);
        /* список уникальных слов в запросе */
        std::set<std::string> words_set;

        std::string word;
        std::stringstream buffer_stream(i);
        std::string toRemove = "\"";

        /* разбитие запроса на отдельные слова и формирование списка уникальных */
        while (buffer_stream >> word)
        {

        std::size_t pos;
        while ((pos = word.find(toRemove)) != std::string::npos) {
            word.erase(pos, toRemove.size());
        }
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word.empty())
            {
                break;
            }
            words_set.insert(word);
        }

        /* по doc_id добавляем количество встреч слова */
        for (const auto& s : words_set)
        {
            std::vector<Entry> word_entry = _index.GetWordCount(s);
            for (const auto& e : word_entry)
            {
                absolute_relevance[e.doc_id] += e.count;
            }
        }

        /* считаем относительную релевантность документов запросу */

        /* максимальная релевантность */
        auto max = std::max_element(absolute_relevance.begin(), absolute_relevance.end());
        /* рассчитываем относительную релевантность */
        if (max != absolute_relevance.end() && *max != 0)
        {
            for (size_t j = 0; j < absolute_relevance.size(); j++)
            {
                if (absolute_relevance[j] > 0)
                {
                    result_inner.emplace_back(RelativeIndex{ .doc_id = j, .rank = ((float)absolute_relevance[j] / *max) });
                }
            }
            std::sort(result_inner.begin(), result_inner.end(), [](RelativeIndex& a, RelativeIndex& b)
            {
                return a.rank > b.rank || (a.rank > (b.rank - 0.000001) && a.rank < (b.rank + 0.000001) && a.doc_id < b.doc_id);
            });
        }
        if (response_limit < result_inner.size())
        {
            result_inner.resize(response_limit);
        }
        result.emplace_back(result_inner);
    }

    std::vector<std::vector<std::pair<int, float>>> result_pairs(result.size());
    for (size_t i = 0; i < result.size(); i++)
    {
        result_pairs[i].resize(result[i].size());
        for (size_t j = 0; j < result[i].size(); j++)
        {
            result_pairs[i][j].first = result[i][j].doc_id;
            result_pairs[i][j].second = result[i][j].rank;
        }
    }

    converter.putAnswers(result_pairs);

    return result;
}