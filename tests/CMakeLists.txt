cmake_minimum_required(VERSION 3.30)

project("search_engine_test" VERSION 1.0)

include(FetchContent)

# Скачиваем gtest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Собираем тестовые файлы
file(
        GLOB TARGET_TEST
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

include(GoogleTest)
gtest_discover_tests(search_engine_test)