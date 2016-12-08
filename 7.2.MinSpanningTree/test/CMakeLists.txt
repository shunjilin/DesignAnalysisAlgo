set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MinHeapTest MinHeapTest.cpp)
add_executable(MinSpanningTreeTest MinSpanningTreeTest.cpp)

target_link_libraries(MinHeapTest gmock pthread)
target_link_libraries(MinSpanningTreeTest gmock pthread)
