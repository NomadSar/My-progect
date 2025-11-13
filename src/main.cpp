#include <windows.h>
#include "coverter.h"
#include "inverted_index.h"
#include "Seachserver.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);

    ConverterJSON converter;
    converter.get_path();
    std::cout << "Engine: " << converter.GetEngineName() << " v." << converter.Get_number_version() << "\n";

    /* создать объект-индекс */
    InvertedIndex idx;

    /* считать содержимое всех документов из файла конфигурации */
    std::vector<std::string> documents = converter.GetTextDocuments();

    /* Обновить базу данных документов в объекте-индексе */
    idx.UpdateDocumentBase(documents);

    /* создать объект-сервер */
    SearchServer server(idx);

    /* получить все запросы из файла запросов */
    std::vector<std::string> requests = converter.GetRequests();

    /* получить результаты поиска (в файл answers.json) */
    std::vector<std::vector<RelativeIndex>> search_result = server.search(requests);
}


