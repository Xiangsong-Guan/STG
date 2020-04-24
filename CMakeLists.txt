cmake_minimum_required(VERSION 3.0.0)
project(STG VERSION 0.1.0)


set(global_include "C:/Users/社会主义二号/pauwaaaa/include")
set(global_lib "C:/Users/社会主义二号/pauwaaaa/lib")

find_library(libglfw3 glfw3 ${global_lib})
find_library(libb2 box2d ${global_lib})

set(ex_source glad.c stb_image.cpp)
set(engine_source game.cpp resource_manger.cpp shader.cpp texture.cpp input_processor.cpp sprite_renderer.cpp game_event.cpp charactor.cpp)

add_executable(STG main.cpp ${ex_source} ${engine_source})
target_include_directories(STG PUBLIC ${global_include})
target_link_libraries(STG ${libglfw3})
target_link_libraries(STG ${libb2})
set_property(TARGET STG PROPERTY CXX_STANDARD 17)
