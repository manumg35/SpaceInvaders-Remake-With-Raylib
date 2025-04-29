cmake_minimum_required(VERSION 3.15)
project(SpaceInvadersRemake)

set(CMAKE_CXX_STANDARD 17)

# Add raylib via FetchContent or use find_package if installed globally
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        4.5.0
)
FetchContent_MakeAvailable(raylib)

# Include source files from src/ folders and main.cpp from root
file(GLOB_RECURSE SRC_FILES
    src/components/*.cpp
    src/events/*.cpp
    src/core/*.cpp
    src/systems/*.cpp
    src/*.cpp
)
set(SOURCES ${SRC_FILES} main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/components
    src/events
    src/core
    src/systems
)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Set the executable output directory
set_target_properties(SpaceInvadersRemake PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy the 'textures' directory to the build folder
file(COPY textures DESTINATION "${CMAKE_BINARY_DIR}/bin")

# On Windows, include extra dependencies
if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm gdi32 opengl32)
endif()