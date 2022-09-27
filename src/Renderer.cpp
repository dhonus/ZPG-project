//
// Created by daniel on 26.9.22.
//

#include "Renderer.h"

int Renderer::render(){
    while (!glfwWindowShouldClose(window->getWindow())){
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
        // update other events like input handling
        glfwPollEvents();

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window->getWindow());
    }
}

Renderer::Renderer(Window* t_window, GLuint shaderProgram, GLuint VAO) {
    this->window = t_window;
    this->VAO = VAO;
    this->shaderProgram = shaderProgram;
}
