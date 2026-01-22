cmake_minimum_required(VERSION 3.20)
project(AegisCore LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(AegisCore
    src/core/Event.cpp
)

target_include_directories(AegisCore
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(tests)
