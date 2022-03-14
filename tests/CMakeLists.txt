project(gtest-demo LANGUAGES CXX)

#set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

#set(SOURCES ${TEST_SOURCES})
add_executable(unit_tests ${TEST_SOURCES})
#add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(unit_tests PUBLIC gtest_main)
