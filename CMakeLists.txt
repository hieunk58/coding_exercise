cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# project variables
set(LOCAL_PROJECT_NAME          "#{bmw_project}")
set(LOCAL_PROJECT_VERSION       "1.0")
set(LOCAL_PROJECT_DESCRIPTION   "This is an exercise")

#project setup
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX
)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)
add_subdirectory(lib/pugixml)

# Doxygen
option(BUILD_DOC "Buid Doxygen Documentation" ON)

find_package(Doxygen)
if(DOXYGEN_FOUND)
set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    # Doxyfile.in
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    # Doxyfile.out
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build starting")

    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

else(DOXYGEN_FOUND)
    message(Doxygen not found!)
endif(DOXYGEN_FOUND)
