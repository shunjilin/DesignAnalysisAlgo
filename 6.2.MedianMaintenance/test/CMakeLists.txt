set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MedianMaintenanceTest MedianMaintenanceTest.cpp)
target_link_libraries(MedianMaintenanceTest gmock pthread)
