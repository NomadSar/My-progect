# Требуемая минимальная версия CMake
cmake_minimum_required(VERSION 3.30)

# Название и версия тестового проекта
project("search_engine_test" VERSION 1.0)

# Добавляем сторонние библиотеки
include(FetchContent)

# Скачиваем gtest из GitHub репозитория (если еще не скачан)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

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













