cmake_minimum_required(VERSION 3.10)
project(CoveragePlanner)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_executable(coverage_planner
    src/main.cpp
    src/map_generator.cpp
    src/planner.cpp
    src/visualizer.cpp
)


target_link_libraries(coverage_planner ${OpenCV_LIBS})
