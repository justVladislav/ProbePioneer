cmake_minimum_required(VERSION 3.25)


add_executable(SkillBoxSearchEngine main.cpp ${MY_INCLUDE_DIR}/converterJson.h converterJson.cpp
                ${MY_INCLUDE_DIR}/invertedIndex.h invertedIndex.cpp
        relativeIndex.cpp
        ${MY_INCLUDE_DIR}/relativeIndex.h ${MY_INCLUDE_DIR}/programInterface.h programInterface.cpp )

include_directories(../includes)

set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/converterJson.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/invertedIndex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/relativeIndex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/programInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(SearchEngineLibrary STATIC ${SOURCE_FILES})

target_include_directories(SkillBoxSearchEngine PUBLIC ${MY_INCLUDE_DIR})
target_include_directories(SearchEngineLibrary PUBLIC
        ${MY_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/nlohmann_json/include
)

