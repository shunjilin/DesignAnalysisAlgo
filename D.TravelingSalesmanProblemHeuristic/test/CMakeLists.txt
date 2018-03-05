set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MapTest MapTest.cpp)
add_executable(TSPHeuristicTest TSPHeuristicTest.cpp)

target_link_libraries(MapTest gmock pthread)
target_link_libraries(TSPHeuristicTest gmock pthread)
