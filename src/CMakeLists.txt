cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(text-analyze)

set(SOURCES_FILES 
    main.cpp
    text_analyze.h
    text_analyze.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/lib/pugixml/src/)

# set bin folder for output
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# exe file bmw_run
add_executable(bmw_run ${SOURCES_FILES})
# lib bmw_lib
add_library(bmw_lib STATIC ${SOURCES_FILES})

# link pugixml
target_link_libraries(bmw_run PUBLIC pugixml)
