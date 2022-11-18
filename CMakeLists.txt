cmake_minimum_required(VERSION 3.24)

project(ZPG)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# add sources
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")
file(GLOB MODELS "models/*.h")
file(GLOB LIBS "lib/*.h")
add_executable(ZPG main.cpp ${SOURCES} ${HEADERS} ${MODELS} ${LIBS})

# link libraries
find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(ZPG glfw)
find_package(GLEW REQUIRED)
    target_link_libraries(ZPG GLEW::GLEW)
find_package(OpenGL REQUIRED)
    target_link_libraries(ZPG OpenGL::GL)
find_package(assimp REQUIRED)
    target_link_libraries(ZPG assimp)