project(gtest-demo LANGUAGES CXX)

set(TEST_SOURCES 
    main.cpp
    unit_tests/test_text_analyze.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests PUBLIC bmw_lib pugixml gtest_main)

# coverage
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if (CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    # we need to turn off optimization for non-skewed coverage reports
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

    # importantly, set the path to the gcovr executable that you downladed
    #set(GCOVR_PATH "/home/ciaran/miniconda3/bin/gcovr")
    # Works
    setup_target_for_coverage_gcovr_xml(
            NAME coverage
            EXECUTABLE unit_tests
            DEPENDENCIES unit_tests bmw_lib
    )
endif()
