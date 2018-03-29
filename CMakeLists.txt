cmake_minimum_required(VERSION 3.1)

project(lemmatizer)

set (CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)
include_directories(include)

add_library(${PROJECT_NAME} ${SRC_LIST})