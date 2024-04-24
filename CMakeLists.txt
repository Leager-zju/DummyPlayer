cmake_minimum_required(VERSION 3.0.0)
project(dummyplayer VERSION 0.1.0 LANGUAGES C CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

find_package(Protobuf REQUIRED)

# include files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROTOBUF_INCLUDE_DIRS}
)

# source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp")
add_executable(dummyplayer ${SRC_FILES})

# compile
add_definitions(-DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1)
target_compile_options(dummyplayer -Wall -Werror -std=c++17 -g -O3)

# link
target_link_libraries(
    dummyplayer
    ${PROTOBUF_LIBRARIES}
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)