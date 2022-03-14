cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

# project variables
set(LOCAL_PROJECT_NAME          "#{bmw_project}")
set(LOCAL_PROJECT_VERSION       "1.0")
set(LOCAL_PROJECT_DESCRIPTION   "This is an exercise")

#set(HEADERS xx.h)
set(SOURCES_FILES src/main.cpp)

add_subdirectory(tests)
add_subdirectory(lib/googletest)

#project setup
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX
)

# set bin folder for output
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(bmw_run ${SOURCES_FILES})
