cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME Bank_System)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES main.cpp Account.cpp Account.h FileStructure.h AccountManager.cpp AccountManager.h View.cpp View.h Transaction.cpp Transaction.h Date.cpp Date.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_library(core ${SOURCE_FILES})

target_link_libraries(Bank_System core)
add_subdirectory(Google_tests)

