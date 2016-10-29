set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(MinCutTest MinCutTest.cpp)
target_link_libraries(MinCutTest gmock pthread)
