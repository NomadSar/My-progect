cmake_minimum_required(VERSION 3.21)

# Применяемый стандарт C++
set(CMAKE_CXX_STANDARD 14 )
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Название корневого проекта (этот проект не собирается)
project(search_project)


# добавляем поддиректорию движка
add_subdirectory(src)

# добавляем поддиректорию тестов
add_subdirectory(tests)
