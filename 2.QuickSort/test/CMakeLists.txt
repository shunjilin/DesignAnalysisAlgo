set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(tests tests.cpp)
target_link_libraries(tests gmock pthread)
