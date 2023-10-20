cmake_minimum_required(VERSION 3.20)
project(bahoth)


file(GLOB SOURCES src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/lib)


find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

find_package(cglm REQUIRED)
include_directories("C:/Program Files (x86)/cglm/include")