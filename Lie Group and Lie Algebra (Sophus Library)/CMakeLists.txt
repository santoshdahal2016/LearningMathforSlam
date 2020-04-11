cmake_minimum_required(VERSION 3.15)
project(LearningC__)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED)

include_directories("/usr/include/eigen3" )


find_package(Sophus REQUIRED)
include_directories("/usr/include/Sophus" )

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(useSophus useSophus.cpp)

add_executable(trajectoryError trajectoryError.cpp)
target_link_libraries(trajectoryError ${Pangolin_LIBRARIES})
