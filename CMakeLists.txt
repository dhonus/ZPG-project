cmake_minimum_required(VERSION 3.24)
project(ogl_tst_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(ogl_tst_02 main.cpp src/Window.cpp include/Window.h src/Renderer.cpp include/Renderer.h src/Shader.cpp include/Shader.h src/App.cpp include/App.h src/Vbo.cpp include/Vbo.h src/Vao.cpp include/Vao.h)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(ogl_tst_02 glfw)

find_package(GLEW REQUIRED)
target_link_libraries(ogl_tst_02 GLEW::GLEW)

find_package(OpenGL REQUIRED)
target_link_libraries(ogl_tst_02 OpenGL::GL)