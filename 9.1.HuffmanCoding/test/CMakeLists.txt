set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(HuffmanTreeTest HuffmanTreeTest.cpp)
add_executable(HuffmanCodingTest HuffmanCodingTest.cpp)

target_link_libraries(HuffmanTreeTest gmock pthread)
target_link_libraries(HuffmanCodingTest gmock pthread)
