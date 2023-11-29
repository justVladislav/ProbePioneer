cmake_minimum_required(VERSION 3.25)

add_executable(SkillBoxSearchEngine 
                main.cpp 
                ${MY_INCLUDE_DIR}/converterJson.h 
                converterJson.cpp
                ${MY_INCLUDE_DIR}/invertedIndex.h 
                invertedIndex.cpp        
                ${MY_INCLUDE_DIR}/relativeIndex.h 
                relativeIndex.cpp
                ${MY_INCLUDE_DIR}/programInterface.h 
                programInterface.cpp              
)

target_include_directories(SkillBoxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/answers.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/requests.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})