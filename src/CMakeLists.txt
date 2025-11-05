# Требуемая минимальная версия CMake
cmake_minimum_required(VERSION 3.21)

# Название и версия основного проекта
project("search_engine" VERSION 1.0)

# Создаем переменную, хранящую пути к файлам
file(
        GLOB TARGET_SRC
        main.cpp
        ../include/main.h
)

# Создаем переменную, хранящую пути к заголовочным файлам библиотеки
file(
        GLOB HEADER_LIB
        ../include/*.h
)

# Создаем переменную, хранящую пути к файлам реализации библиотеки
# Исправлено: убраны неправильные шаблоны, оставьте свои пути
file(
        GLOB SOURCE_LIB
        ../include/*.cpp
)

# Создаем библиотеку для последующего использования (например, в тестах)
add_library(MySearchEngineLib ${HEADER_LIB} ${SOURCE_LIB})

# Включаем сторонние библиотеки
include(FetchContent)

# Отключаем модульные тесты для json
set(JSON_BuildTests OFF CACHE INTERNAL "")

cmake_policy(SET CMP0135 NEW)
# Скачиваем nlohmann_json
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Связываем библиотеку json с нашей библиотекой
target_link_libraries(
        MySearchEngineLib
        nlohmann_json::nlohmann_json
)

# Создаем основной исполняемый файл
add_executable(
        search_engine
        ${TARGET_SRC}
)

target_link_libraries(
        search_engine
        MySearchEngineLib
)

