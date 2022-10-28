//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"
#include "../models/sphere.h"
#include "../models/suzi_smooth.h"
#include "../models/cube.h"
#include "../models/floor.h"
#include "../models/tree.h"
#include "../models/bush.h"
#include "../models/gift.h"

int Scene::render() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    while (!glfwWindowShouldClose(window->getWindow())) {
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        //glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        //glClearColor(0.5f, 0.7f, 0.9f, 1.0f);

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
    srand(time(NULL));

    this->window = t_window;
    this->callbacks = new Callbacks(*this->window->getWindow());
    this->camera = new Camera(width, height, *callbacks);
    this->callbacks->setCamera(this->camera);
    this->callbacks->attach(this->camera);

    std::shared_ptr<Composite> baseOrbit = std::make_shared<Trans>();

    /*baseOrbit
            ->add(std::make_shared<TransMove>(glm::vec3{0.0f, 2.0f, 2.0f}))
            ->add(std::make_shared<TransRotate>(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)))
            ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));
*/
    baseOrbit->add(std::make_shared<TransMove>(glm::vec3(20.0, 0.0, 20.0)));
    baseOrbit->add(std::make_shared<TransRotate>(true, 180, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    std::shared_ptr<Composite> pohnoutKoulema = std::make_shared<Trans>();
    pohnoutKoulema
            ->add(std::make_shared<TransMove>(glm::vec3{15.0f, 15.0f, 0.0f}));

    /* SHADERS */
    std::shared_ptr<Shader> floorShader = std::make_shared<Shader>("floor.vs", "floor.fs", camera);
    std::shared_ptr<Shader> basicLightShader = std::make_shared<Shader>("light.vs", "light.fs", camera);
    std::shared_ptr<Shader> cutLightShader = std::make_shared<Shader>("cutLight.vs", "cutLight.fs", camera);
    std::shared_ptr<Shader> hezkeKouleShader = std::make_shared<Shader>("4_hezke_koule.vs", "4_hezke_koule.fs", camera);
    std::shared_ptr<Shader> treeShader = std::make_shared<Shader>("treeShader.vs", "treeShader.fs", camera);
    std::shared_ptr<Shader> gouraudShader = std::make_shared<Shader>("gouraud.vs", "gouraud.fs", camera);


    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(cutLightShader)
            ->add(std::make_shared<TransRotate>(true, 2.5f, -glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 5.0f)));

    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(basicLightShader)
            ->add(baseOrbit)
            ->add(std::make_shared<TransRotate>(2.5f, -glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 5.0f)))
            ->add(std::make_shared<TransScale>(0.6f));

    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(basicLightShader)
            ->add(baseOrbit)
            ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(5.0f, 0.0f, 5.0f)))
            ->add(std::make_shared<TransScale>(0.3f));


    addObjectToScene(
            std::make_shared<Object>(
                suziSmooth,
                GL_TRIANGLES,
                2904, 3, 3, 3, 6 )
            )->linkShader(basicLightShader)->add(baseOrbit);

    addObjectToScene(
            std::make_shared<Object>(
                    floor_model,
                    GL_POLYGON,
                    4, 4, 4, 4, 8))
            ->linkShader(floorShader);

    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(3.0, 0.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(-3.0, 0.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(0.0, 3.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(
                    sphere,
                    GL_TRIANGLES,
                    2880, 3, 3, 3, 6))
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(0.0, -3.0, 0.0)));


    std::shared_ptr<TransMove> forestMove = std::make_shared<TransMove>(glm::vec3(20.0, -5.0, 20.0));
    addObjectToScene(
            std::make_shared<Object>(
                    gift,
                    GL_TRIANGLES,
                    66624, 3, 3, 3, 6))
            ->linkShader(gouraudShader)
            ->add(forestMove)
            ->add(std::make_shared<TransMove>(glm::vec3(2.0f, 0.0f, -4.0f)))
            ->add(std::make_shared<TransScale>(5.0f));

    for (size_t i = 0; i < 50; ++i){
        addObjectToScene(
                std::make_shared<Object>(
                        tree,
                        GL_TRIANGLES,
                        92814, 3, 3, 3, 6)
        )
                ->linkShader(treeShader)
                ->add(forestMove)
                ->add(std::make_shared<TransMove>(glm::vec3(rand() % 70, 0.0, rand() % 60)));
    }

    for (size_t i = 0; i < 500; ++i){
        addObjectToScene(
                std::make_shared<Object>(
                        bush,
                        GL_TRIANGLES,
                        8730, 3, 3, 3, 6)
        )
                ->linkShader(treeShader)
                ->add(forestMove)
                ->add(std::make_shared<TransMove>(glm::vec3(rand() % 70  + (rand() % 50 * 0.1), 0.0, rand() % 60  + (rand() % 50 * 0.1))))
                ->add(std::make_shared<TransRotate>(true, rand() % 120, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    }


    this->hud = new Hud;
}

std::shared_ptr<Object> Scene::addObjectToScene(std::shared_ptr<Object> object){
    this->objects.push_back(object);
    return object;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}

