cmake_minimum_required(VERSION 3.25)

project(SkillBoxSearchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/includes)

add_subdirectory(sourceFiles)
add_subdirectory(googleTest)
add_subdirectory(nlohmann_json)

find_package(nlohmann_json QUIET)
if(nlohmann_json_FOUND)
    target_link_libraries(SkillBoxSearchEngine PRIVATE nlohmann_json::nlohmann_json)
else()
    message(FATAL_ERROR "nlohmann/json library not found. Please install it.")
endif()



