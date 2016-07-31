set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(inversions main.cpp)
target_link_libraries(inversions gmock pthread)
