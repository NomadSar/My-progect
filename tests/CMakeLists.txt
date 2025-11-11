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
#
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















