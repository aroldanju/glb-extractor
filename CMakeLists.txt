cmake_minimum_required(VERSION 3.14)

project(glb-extractor)

file(GLOB GLBEXTRACTOR_SOURCES src/*.cpp)

add_subdirectory(src/libglb)

include_directories(src/libglb)

add_executable(${PROJECT_NAME} ${GLBEXTRACTOR_SOURCES} ${LIBGLB_SOURCES})
target_link_libraries(${PROJECT_NAME} dependencies::libglb)
