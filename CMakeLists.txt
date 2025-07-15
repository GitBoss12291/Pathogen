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

include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

add_subdirectory(deps/glfw3)

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/deps/glad/src/gl.c "src/shader.cpp") # If using vulkan, change the name of this file to vulkan.c
target_include_directories(glad PUBLIC deps/glad/include deps/stb_image deps/glfw3/include)

add_executable(Pathogen main.cpp
    "src/sprite_renderer.cpp"
    "src/shader.cpp"
 "src/game.cpp"  "src/input_handler.cpp" "src/game_object.cpp" "src/player.cpp" "src/enemy.cpp" "src/cell.cpp" "src/part.cpp" "src/editor.cpp" "src/ui_panel.cpp")

add_custom_command(TARGET Pathogen POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Pathogen>/assets)

target_include_directories(Pathogen PRIVATE ${CMAKE_SOURCE_DIR}/src ${GLFW3_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/deps/glad/include)
target_link_libraries(Pathogen PRIVATE glad glfw glm::glm)