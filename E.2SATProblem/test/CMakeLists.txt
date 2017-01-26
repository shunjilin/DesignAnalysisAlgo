set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(SCCTest SCCTest.cpp)
add_executable(2SATTest 2SATTest.cpp)
  
target_link_libraries(SCCTest gmock pthread)
target_link_libraries(2SATTest gmock pthread)
