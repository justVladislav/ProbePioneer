cmake_minimum_required(VERSION 3.25)

project(SkillBoxSearchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/includes)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_subdirectory(sourceFiles)
add_subdirectory(googleTest)

target_link_libraries(SkillBoxSearchEngine PRIVATE nlohmann_json::nlohmann_json)


