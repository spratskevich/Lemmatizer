cmake_minimum_required(VERSION 3.1)

project(lemmatizer)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
aux_source_directory(src SRC_LIST)

add_library(${PROJECT_NAME} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY bin
    LIBRARY_OUTPUT_DIRECTORY bin
    RUNTIME_OUTPUT_DIRECTORY bin
)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Test REQUIRED)

aux_source_directory(test/src TEST_SRC_LIST)
foreach(TEST_SRC ${TEST_SRC_LIST})
    get_filename_component(TEST ${TEST_SRC} NAME_WE)
    add_executable(${TEST} ${TEST_SRC})
    target_include_directories(${TEST} PRIVATE ${PROJECT_BINARY_DIR})
    target_link_libraries(${TEST} ${PROJECT_NAME} Qt5::Test)
    set_target_properties(${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY test/bin)
endforeach(TEST_SRC)