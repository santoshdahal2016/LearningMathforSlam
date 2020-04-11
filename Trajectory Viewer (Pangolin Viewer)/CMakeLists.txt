cmake_minimum_required(VERSION 3.15)
project(Trajectory_Viewer)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED)

include_directories("/usr/include/eigen3" )

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(poseViewer poseViewer.cpp)
target_link_libraries(poseViewer ${Pangolin_LIBRARIES})
