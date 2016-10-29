set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(SCCTest SCCTest.cpp)
target_link_libraries(SCCTest gmock pthread)
