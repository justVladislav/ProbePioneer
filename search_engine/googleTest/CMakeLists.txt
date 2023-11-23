cmake_minimum_required(VERSION 3.25)

project(GoogleTest VERSION 0.1 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(../includes
                    ../sourceFiles)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(GoogleTest testInvertedIndexClass.cpp searchServerClass.cpp ../includes/converterJson.h
        ../includes/relativeIndex.h ../includes/invertedIndex.h
        ../sourceFiles/invertedIndex.cpp ../sourceFiles/relativeIndex.cpp ../sourceFiles/converterJson.cpp)


target_link_libraries(GoogleTest PRIVATE gtest gtest_main)
target_link_libraries(GoogleTest PRIVATE nlohmann_json::nlohmann_json)

include(GoogleTest)

gtest_discover_tests(GoogleTest)

