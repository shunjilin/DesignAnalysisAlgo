set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(UnionFindTest UnionFindTest.cpp)
add_executable(BitFunctionsTest BitFunctionsTest.cpp)
add_executable(ClusteringTest ClusteringTest.cpp)

target_link_libraries(BitFunctionsTest gmock pthread)
target_link_libraries(UnionFindTest gmock pthread)
target_link_libraries(ClusteringTest gmock pthread)
