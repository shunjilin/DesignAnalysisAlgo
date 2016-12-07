set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")

add_executable(SchedulerTest SchedulerTest.cpp)

target_link_libraries(SchedulerTest gmock pthread)
