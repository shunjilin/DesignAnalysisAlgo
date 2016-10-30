set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(TwoSumTest TwoSumTest.cpp)
target_link_libraries(TwoSumTest gmock pthread)
