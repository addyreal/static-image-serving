cmake_minimum_required(VERSION 3.12)
project(static-image-convert)

# C++ std
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ./src, ./external
set(SRC_DIR ./src)
set(SRCS ${SRC_DIR}/main.cpp ${SRC_DIR}/utils.cpp ${SRC_DIR}/conversion.cpp ${SRC_DIR}/config.cpp)
set(INCLUDE_DIR ./external/includes)
set(LINK_DIR ./external/libs)

# tool
add_executable(static-image-convert ${SRCS})

include_directories(${INCLUDE_DIR})
target_include_directories(static-image-convert PRIVATE ${INCLUDE_DIR})
target_link_directories(static-image-convert PRIVATE ${LINK_DIR})
target_link_libraries(static-image-convert PRIVATE yaml-cpp webp)

# macro for source dir
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# install
install(TARGETS static-image-convert DESTINATION /usr/local/bin)