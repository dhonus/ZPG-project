//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"
#include "../models/sphere.h"
#include "../models/suzi_flat.h"
#include "../models/cube.h"
#include "../models/floor.h"
int Scene::render() {
    std::shared_ptr<Composite> baseOrbit = std::make_shared<Trans>();

    /*baseOrbit
        ->add(std::make_shared<TransMove>(glm::vec3{0.0f, 2.0f, 2.0f}))
        ->add(std::make_shared<TransRotate>(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)))
        ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));
*/
    this->objects.at(0)->add(baseOrbit);
    this->objects.at(1)->add(baseOrbit);
    this->objects.at(2)->add(baseOrbit);

    this->objects.at(0)
        ->add(std::make_shared<TransRotate>(2.5f, -glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 5.0f)))
        ->add(std::make_shared<TransScale>(0.5f));

    this->objects.at(1)
        ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(5.0f, 0.0f, 5.0f)))
        ->add(std::make_shared<TransScale>(0.3f));

    this->objects.at(3)
        ->add(std::make_shared<TransRotate>(true, 0.5f, -glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
        ->add(std::make_shared<TransScale>(200.0f));

    this->objects.at(4)
        ->add(std::make_shared<TransMove>(glm::vec3(5.0, 10.0, 20.0)));
    this->objects.at(5)->add(std::make_shared<TransMove>(glm::vec3(2.0, 0.0, 3.0)));


    while (!glfwWindowShouldClose(window->getWindow())) {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // This makes the movement with WASD immediate.
        // A callback is unusable for this.
        camera->move (
                glfwGetKey( window->getWindow(), GLFW_KEY_W ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_S ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_A ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_D ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_SPACE ) == GLFW_PRESS,
                glfwGetKey( window->getWindow(), GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS );

        for (auto & o : this->objects) o->draw();

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
                    "regular.fs",
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
                    "regular.fs",
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
                "basic_light.vs",
                "basic_light.fs",
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
                    "regular.fs",
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
                    "basic_light.vs",
                    "basic_light.fs",
                    camera,
                    GL_TRIANGLES,
                    2880,
                    3,
                    2,
                    3,
                    6
            ));
    this->objects.push_back(
            std::make_unique<Object>(
                    cube,
                    "basic_light.vs",
                    "basic_light.fs",
                    camera,
                    GL_TRIANGLES,
                    36,
                    3,
                    2,
                    3,
                    5));

    this->hud = new Hud;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}
