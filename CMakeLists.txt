cmake_minimum_required(VERSION 3.30)

# Применяемый стандарт C++
set(CMAKE_CXX_STANDARD 14 )

include_directories(
        include
        src
)

# Название корневого проекта (этот проект не собирается)
project(search_project)


# добавляем поддиректорию движка
add_subdirectory(src)

# добавляем поддиректорию тестов
add_subdirectory(tests)
