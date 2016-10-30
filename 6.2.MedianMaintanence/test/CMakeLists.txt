set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MedianMaintanenceTest MedianMaintanenceTest.cpp)
target_link_libraries(MedianMaintanenceTest gmock pthread)
