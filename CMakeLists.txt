cmake_minimum_required(VERSION 3.16)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")

file(GLOB
        CPP_SOURCES "*src/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

include(FetchContent)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(json)


target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

#
## FetchContent for nlohmann_json
#include(FetchContent)
#FetchContent_Declare(
#        nlohmann_json
#        URL https://github.com/nlohmann/json/archive/v3.12.0.tar.gz # Using the .tar.gz version
#        # set files' timestamps to time of extraction
#        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
#)
#FetchContent_MakeAvailable(nlohmann_json)
#
## Create executable

#
## Link nlohmann_json to the executable
