set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(BellManFordTest BellManFordTest.cpp)
add_executable(MinHeapTest MinHeapTest.cpp)
add_executable(DijkstraTest DijkstraTest.cpp)
add_executable(JohnsonsAlgoTest JohnsonsAlgoTest.cpp)

target_link_libraries(BellManFordTest gmock pthread)
target_link_libraries(MinHeapTest gmock pthread)
target_link_libraries(DijkstraTest gmock pthread)
target_link_libraries(JohnsonsAlgoTest gmock pthread)
