cmake_minimum_required(VERSION 2.8)

project(study_libxml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

include_directories(
  /usr/include/libxml2
)

add_executable(study_libxml main.cpp)
target_link_libraries(study_libxml xml2)
