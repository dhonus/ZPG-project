//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"

int Scene::render() {
    while (!glfwWindowShouldClose(window->getWindow())) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //setshader
        this->objects.at(0)->trans->rotate(.7, 1);
        this->objects.at(1)->trans->scale();
        this->objects.at(1)->trans->rotate(1.3, -1);

        for (auto & o : this->objects){
            o->draw();
        }

        // this makes the movement with WASD not suck. A callback is completely unusable for this.
        camera->move (
                glfwGetKey( window->getWindow(), GLFW_KEY_W ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_S ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_A ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_D ) == GLFW_PRESS );

        // update other events like input handling
        glfwPollEvents();

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window->getWindow());
    }
    return 0;
}

Scene::Scene(std::shared_ptr<Window> t_window, int width, int height) {
    this->window = t_window;
    this->camera = std::make_shared<Camera>(width, height);
    this->callbacks = std::make_shared<Callbacks>(this->window->getWindow());
    this->callbacks->setCamera(this->camera);
    this->objects.push_back(std::make_unique<Object>(b, "box_regular.vs", camera));
    this->objects.push_back(std::make_unique<Object>(b2, "box_regular.vs", camera));
}
