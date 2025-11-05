cmake_minimum_required(VERSION 3.16)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Добавляем сторонние библиотеки
include(FetchContent)

# Скачиваем gtest из GitHub репозитория (если еще не скачан)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
#
# Добавляем директорию gtest
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Параметр управления многопоточностью
set(gtest_disable_pthreads on)

# Предотвращение переопределения настроек компилятора/компоновщика родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Открытие доступности скаченных из GitHub репозитория данных
FetchContent_MakeAvailable(googletest)

enable_testing()


file(
    GLOB TARGET_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
    search_engine_test
    ${TARGET_TEST}
)

target_link_libraries(search_engine_test PRIVATE
    gtest_main
    MySearchEngineLib
)

include(googletest)

















# # Минимально требуемая версия CMake
# cmake_minimum_required(VERSION 3.30)

# # Название и версия проекта
# project("search_engine_test" VERSION 1.0)

# # Применяемый стандарт C++
# set(CMAKE_CXX_STANDARD 20)

# # необходимо для сборки тестового приложения
# add_compile_definitions(__TEST_SEARCH_ENGINE__)

# # Включение своих директорий
# include_directories(
#     ../inc
#     ../tests
# )

# # Добавление сторонних библиотек
# include(FetchContent)

# # Отключение модульных тестов для библиотеки json
# set(JSON_BuildTests OFF CACHE INTERNAL "")

# # Скачивание nlohmann json из GitHub репозитория
# FetchContent_Declare(
#     json
#     URL
#     https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
# )

# # Скачивание google test из GitHub репозитория
# FetchContent_Declare(
#     googletest
#     URL
#     https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
# )

# #----------
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# set(gtest_disable_pthreads on)
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# # Открытие доступности скаченных из GitHub репозитория данных о json
# FetchContent_MakeAvailable(json googletest)

# #----------
# enable_testing()

# # Добавление своих файлов в проект
# add_executable(
#     search_engine_test

#     tests.hpp
#     tests.cpp
#     TestCaseInvertedIndex.cpp
#     TestCaseSearchServer.cpp

#     ../src/main.cpp

#     ../inc/ConverterJSON.hpp
#     ../src/ConverterJSON.cpp

#     ../inc/InvertedIndex.hpp
#     ../src/InvertedIndex.cpp

#     ../inc/SearchServer.hpp
#     ../src/SearchServer.cpp

#     ../inc/exceptions.hpp
#     )

# target_link_libraries(search_engine_test PRIVATE nlohmann_json::nlohmann_json)

# #----------
# target_link_libraries(search_engine_test PRIVATE gtest_main)
# include(googletest)
