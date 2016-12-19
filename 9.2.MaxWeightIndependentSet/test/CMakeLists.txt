set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")


add_executable(MWISDPTest MWISDPTest.cpp)

target_link_libraries(MWISDPTest gmock pthread)
