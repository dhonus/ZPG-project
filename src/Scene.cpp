//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"
#include "../models/sphere.h"
#include "../models/suzi_flat.h"
#include "../models/cube.h"
#include "../models/floor.h"
int Scene::render() {
    this->objects.at(0)->trans->add(new TransMove({0.0f, 1.0f, 1.0f}));
    this->objects.at(0)->trans->add(new TransRotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
    this->objects.at(0)->trans->add(new TransRotate(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));

    this->objects.at(1)->trans->add(new TransMove({0.0f, 1.0f, 1.0f}));
    this->objects.at(1)->trans->add(new TransRotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
    this->objects.at(1)->trans->add(new TransRotate(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));

    this->objects.at(2)->trans->add(new TransMove({0.0f, 1.0f, 1.0f}));
    this->objects.at(2)->trans->add(new TransRotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
    this->objects.at(2)->trans->add(new TransRotate(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));

    this->objects.at(0)->trans->add(new TransRotate(2.5f, -glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 5.0f)));
    this->objects.at(0)->trans->add(new TransScale(0.5f));

    this->objects.at(1)->trans->add(new TransRotate(0.5f, -glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(5.0f, 0.0f, 5.0f)));
    this->objects.at(1)->trans->add(new TransScale(0.3f));

    this->objects.at(3)->trans->add(new TransRotate(true, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    this->objects.at(3)->trans->add(new TransScale(200.0f));


    while (!glfwWindowShouldClose(window->getWindow())) {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto & o : this->objects){
            o->draw();
        }

        // This makes the movement with WASD immediate.
        // A callback is unusable for this.
        camera->move (
                glfwGetKey( window->getWindow(), GLFW_KEY_W ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_S ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_A ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_D ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS );

        hud->draw(*camera);

        glfwPollEvents();
        glfwSwapBuffers(window->getWindow());

    }
    return 0;
}

Scene::Scene(std::shared_ptr<Window> t_window, int width, int height) {
    this->window = t_window;
    this->callbacks = new Callbacks(*this->window->getWindow());
    this->camera = new Camera(width, height, *callbacks, window);
    this->callbacks->setCamera(this->camera);
    this->callbacks->attach(this->camera);
    /*
    this->objects.push_back(
            std::make_unique<Object>(
                cube,
                "box_regular.vs",
                camera,
                GL_TRIANGLES,
                36,
                3,
                2,
                3,
                5));*/
    this->objects.push_back(
            std::make_unique<Object>(
                    sphere,
                    "box_regular.vs",
                    camera,
                    GL_TRIANGLES,
                    2880,
                    3,
                    2,
                    3,
                    6));
    this->objects.push_back(
            std::make_unique<Object>(
                    sphere,
                    "box_regular.vs",
                    camera,
                    GL_TRIANGLES,
                    2880,
                    3,
                    2,
                    3,
                    6));
    /*this->objects.push_back(
            std::make_unique<Object>(
                floor_model,
                "box_regular.vs",
                camera,
                GL_POLYGON,
                4,
                4,
                4,
                4,
                8));

   this->objects.push_back(
            std::make_unique<Object>(
                sphere,
                "box_regular.vs",
                camera,
                GL_TRIANGLES,
                2880,
                3,
                2,
                3,
                6
            ));*/
    this->objects.push_back(
            std::make_unique<Object>(
                suziFlat,
                "box_wild.vs",
                camera,
                GL_TRIANGLES,
                2904,
                3,
                2,
                3,
                6
            ));

    this->objects.push_back(
            std::make_unique<Object>(
                    floor_model,
                    "box_regular.vs",
                    camera,
                    GL_POLYGON,
                    4,
                    4,
                    4,
                    4,
                    8));

    this->hud = new Hud;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}
