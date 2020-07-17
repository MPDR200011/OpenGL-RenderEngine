cmake_minimum_required(VERSION 3.12)

project(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GLFW setup
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_SOURCE_DIR}/libs/glfw")

# Load libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

message(STATUS "GLM: " glm)

# Sources
set(SRC
    src/Loader.cpp
    src/Window.cpp
    src/shaders/AbstractShaderProgram.cpp
    src/shaders/static/StaticShaderProgram.cpp
)
add_executable(engine ${SRC} src/main.cpp)

target_compile_options(engine
    PUBLIC -std=c++17 -Wall -pedantic 
)

add_executable(tests ${SRC} test/main.cpp)

target_include_directories(tests PRIVATE src/)

target_compile_options(tests
    PUBLIC -std=c++17
)

# Link glfw
target_link_libraries(engine glfw)
target_link_libraries(tests glfw)

# Link Glew
target_include_directories(engine PRIVATE ${GLEW_INCLUDE_DIRS})
target_include_directories(tests PRIVATE ${GLEW_INCLUDE_DIRS})
message(STATUS "GLEW Library = ${GLEW_LIBRARIES}")
target_link_libraries(engine ${GLEW_LIBRARIES})
target_link_libraries(tests ${GLEW_LIBRARIES})

# Link OpenGL
target_include_directories(engine PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(tests PRIVATE ${OPENGL_INCLUDE_DIR})
message(STATUS "OPENGL Libraries = ${OPENGL_LIBRARIES}")
target_link_libraries(engine ${OPENGL_LIBRARIES})
target_link_libraries(tests ${OPENGL_LIBRARIES})

#Link GLM
target_link_libraries(engine glm)
target_link_libraries(tests glm)
