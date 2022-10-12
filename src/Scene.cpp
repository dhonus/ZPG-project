//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"

int Scene::render() {
    while (!glfwWindowShouldClose(window->getWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //setshader
        this->objects.at(0)->trans->rotate(.7, 1);
        this->objects.at(1)->trans->scale();
        this->objects.at(1)->trans->rotate(1.3, -1);

        for (auto & o : this->objects){
            o->draw();
        }

        // update other events like input handling
        glfwPollEvents();

        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window->getWindow());
    }
    return 0;
}

Scene::Scene(std::shared_ptr<Window> t_window) {
    this->window = t_window;
    this->objects.push_back(std::make_unique<Object>(b, "box_wild.vs"));
    this->objects.push_back(std::make_unique<Object>(b2, "box_regular.vs"));
}
