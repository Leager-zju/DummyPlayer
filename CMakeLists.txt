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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)
target_compile_options(dummyplayer PUBLIC -Wall -Werror -g)

# link
target_link_libraries(
    dummyplayer
    ${PROTOBUF_LIBRARIES}
)

# output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)