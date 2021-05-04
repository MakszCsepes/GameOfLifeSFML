cmake_minimum_required(VERSION 3.5.1)
project(GoL_SFML)

set(CMAKE_CXX_STANDARD 14)

set(SFML_LIBRARY_DIR "SFML-2.5.1/lib")
set(SFML_INCLUDE_DIR "SFML-2.5.1/include")
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(${PROJECT_NAME} main.cpp board.h board.cpp cell.cpp cell.h)
target_link_libraries (${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
