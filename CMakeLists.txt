cmake_minimum_required(VERSION 3.10)

project(RayTracingPractice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Collect all .cpp files in the src directory
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SRC_FILES})

