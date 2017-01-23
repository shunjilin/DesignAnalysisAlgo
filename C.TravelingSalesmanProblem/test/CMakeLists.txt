set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MapTest MapTest.cpp)
add_executable(BitwiseTest BitwiseTest.cpp)
add_executable(TSPDPTest TSPDPTest.cpp)

target_link_libraries(MapTest gmock pthread)
target_link_libraries(BitwiseTest gmock pthread)
target_link_libraries(TSPDPTest gmock pthread)
