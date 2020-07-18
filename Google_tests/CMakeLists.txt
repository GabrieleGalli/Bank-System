# 'Google_test' is the subproject name
set(PROJECT_NAME Google_tests)
project(${PROJECT_NAME})

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)

set(gtest_SOURCE_DIR lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp TESTS.cpp)

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run ${TEST_SOURCE_FILES})
target_link_libraries(Google_Tests_run gtest gtest_main core)