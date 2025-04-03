cmake_minimum_required(VERSION 3.12)
project(tool)

# C++ std
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ./src, ./external
set(SRC_DIR ./src)
set(SRCS ${SRC_DIR}/main.cpp ${SRC_DIR}/utils.cpp ${SRC_DIR}/conversion.cpp ${SRC_DIR}/config.cpp)
set(INCLUDE_DIR ./external/includes)
set(LINK_DIR ./external/libs)

# tool
add_executable(tool ${SRCS})

include_directories(${INCLUDE_DIR})
target_include_directories(tool PRIVATE ${INCLUDE_DIR})
target_link_directories(tool PRIVATE ${LINK_DIR})
target_link_libraries(tool PRIVATE yaml-cpp webp)

# macro for source dir
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")