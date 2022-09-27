cmake_minimum_required(VERSION 3.24)
project(ogl_tst_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(ogl_tst_02 main.cpp src/Window.cpp src/Window.h src/Renderer.cpp src/Renderer.h src/ShaderObject.cpp src/ShaderObject.h src/App.cpp src/App.h)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(ogl_tst_02 glfw)

find_package(GLEW REQUIRED)
target_link_libraries(ogl_tst_02 GLEW::GLEW)

find_package(OpenGL REQUIRED)
target_link_libraries(ogl_tst_02 OpenGL::GL)