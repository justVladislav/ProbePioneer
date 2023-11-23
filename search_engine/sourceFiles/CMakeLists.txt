cmake_minimum_required(VERSION 3.25)


add_executable(SkillBoxSearchEngine main.cpp ${MY_INCLUDE_DIR}/converterJson.h converterJson.cpp
                ${MY_INCLUDE_DIR}/invertedIndex.h invertedIndex.cpp
        relativeIndex.cpp
        ${MY_INCLUDE_DIR}/relativeIndex.h ${MY_INCLUDE_DIR}/programInterface.h programInterface.cpp )

include_directories(../includes)

target_include_directories(SkillBoxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

