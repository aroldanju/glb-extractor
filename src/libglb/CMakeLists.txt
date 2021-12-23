cmake_minimum_required(VERSION 3.14)

project(glb)

file(GLOB LIBGLB_SOURCES *.cpp)

add_library(${PROJECT_NAME} ${LIBGLB_SOURCES})
add_library(dependencies::libglb ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/libglb)
