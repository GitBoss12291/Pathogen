# Used LearnOpenGL CMakeLists.txt for reference. 
# https://github.com/JoeyDevries/LearnOpenGL/blob/master/CMakeLists.txt

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)

project(Pathogen)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if (MSVC)
    foreach(flag_var CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        string(REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
    endforeach()
endif()

add_subdirectory(deps/glfw)

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/deps/glad/src/gl.c) # If using vulkan, change the name of this file to vulkan.c
target_include_directories(glad PUBLIC deps/glad/include)

file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*)

add_executable(Pathogen main.cpp ${SRC})

target_include_directories(Pathogen PRIVATE ${CMAKE_SOURCE_DIR}/src ${GLFW3_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/deps/glad/include)
target_link_libraries(Pathogen PRIVATE glad glfw)