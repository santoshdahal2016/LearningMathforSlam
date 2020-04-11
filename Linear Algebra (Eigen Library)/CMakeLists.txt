cmake_minimum_required(VERSION 3.15)
project(Linear_Algebra)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED)

include_directories("/usr/include/eigen3" )


add_executable(EigenDense EigenDense.cpp)

add_executable(EigenGeometry eigenGeometry.cpp)

add_executable(coordinateTransform coordinateTransform.cpp)
