# Требуемая минимальная версия CMake
cmake_minimum_required(VERSION 3.21)

# Название и версия тестового проекта
project("search_engine_test" VERSION 1.0)

# Включаем поддержку тестирования
enable_testing()

# Добавляем сторонние библиотеки
include(FetchContent)

cmake_policy(SET CMP0135 NEW)
# Скачиваем gtest из GitHub (если еще не скачан)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Предположим, что ваши тестовые файлы находятся в папке tests/
# Используйте правильный путь к папке с тестами
file(
        GLOB TARGET_TEST
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
)

# Создаем тестовый исполняемый файл
add_executable(
        search_engine_test
        ${TARGET_TEST}
)

# Связываем с gtest и вашей библиотекой
target_link_libraries(
        search_engine_test
        gtest_main
        MySearchEngineLib
)

# Регистрация тестов с помощью gtest_discover_tests
include(GoogleTest)
gtest_discover_tests(search_engine_test)




