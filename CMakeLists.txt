cmake_minimum_required(VERSION 3.10)

# Project name and settings
project(SDL_C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find all source files recursively in the src directory
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

# Find SDL2 and OpenGL
find_package(SDL2 REQUIRED)

# Include directories for SDL2 and project headers
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src  # Include all project headers
)

# Add the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link SDL2 and OpenGL libraries
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES} 
    GL
    GLEW)

