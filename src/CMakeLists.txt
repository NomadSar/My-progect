# Требуемая минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название и версия проекта
project(search_engine LANGUAGES CXX)

# Создаем исполняемый файл
add_executable(search_engine main.cpp coverter.cpp inverted_index.cpp Seachserver.cpp static_metod.cpp )

# Включаем директории, если есть переменная MY_INCLUDE_DIR
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})

# Включаем FetchContent
include(FetchContent)

# Отключаем тесты для json
set(JSON_BuildTests OFF CACHE INTERNAL "")

# Объявляем и скачиваем json
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

# Линковка json
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

#[[
# Объявляем и скачиваем googletest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Включаем тестирование
enable_testing()

# Линковка gtest и gtest_main
target_link_libraries(search_engine PRIVATE gtest_main)

# Включаем GoogleTest
include(GoogleTest)
gtest_discover_tests(search_engine)]]
