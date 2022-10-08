cmake_minimum_required(VERSION 3.24)
project(ZPG)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZPG main.cpp src/Window.cpp include/Window.h src/Scene.cpp include/Scene.h src/Shader.cpp include/Shader.h src/App.cpp include/App.h src/Vbo.cpp include/Vbo.h src/Vao.cpp include/Vao.h src/Object.cpp include/Object.h src/SceneManager.cpp include/SceneManager.h src/Model.cpp include/Model.h src/Trans.cpp include/Trans.h)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(ZPG glfw)

find_package(GLEW REQUIRED)
target_link_libraries(ZPG GLEW::GLEW)

find_package(OpenGL REQUIRED)
target_link_libraries(ZPG OpenGL::GL)