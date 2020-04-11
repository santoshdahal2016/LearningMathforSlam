cmake_minimum_required(VERSION 3.15)
project(LearningC__)

set(CMAKE_CXX_STANDARD 14)


add_executable(main main.cpp)

add_subdirectory("./Linear Algebra (Eigen Library)")

add_subdirectory("./Trajectory Viewer (Pangolin Viewer)")

add_subdirectory("./Lie Group and Lie Algebra (Sophus Library)")