set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MinHeapTest MinHeapTest.cpp)
add_executable(UnionFindTest UnionFindTest.cpp)
add_executable(ClusteringTest ClusteringTest.cpp)

target_link_libraries(MinHeapTest gmock pthread)
target_link_libraries(UnionFindTest gmock pthread)
target_link_libraries(ClusteringTest gmock pthread)
