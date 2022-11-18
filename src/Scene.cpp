//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"
#include "../models/sphere.h"
#include "../models/suzi_smooth.h"
#include "../models/suzi_flat.h"
#include "../models/floor.h"
#include "../models/tree.h"
#include "../models/bush.h"
#include "../models/gift.h"
#include "../models/cube.h"

int Scene::render() {
    glEnable(GL_DEPTH_TEST);
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

    /* SCENE SETUP */
    this->window = t_window;
    this->callbacks = new Callbacks(*this->window->getWindow());
    this->camera = new Camera(width, height, *callbacks);
    this->callbacks->setCamera(this->camera);
    this->callbacks->attach(this->camera);

    /* TRANSFORMATIONS */
    std::shared_ptr<Composite> baseOrbit = std::make_shared<Trans>();
    std::shared_ptr<Composite> pohnoutKoulema = std::make_shared<Trans>();
    baseOrbit->add(std::make_shared<TransMove>(glm::vec3(20.0, 0.0, 20.0)));
    baseOrbit->add(std::make_shared<TransRotate>(true, 180, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    baseOrbit ->add(std::make_shared<TransMove>(glm::vec3{0.0f, 2.0f, 2.0f}))->add(std::make_shared<TransRotate>(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)))->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));
    pohnoutKoulema->add(std::make_shared<TransMove>(glm::vec3{15.0f, 15.0f, 0.0f}));
    std::shared_ptr<TransMove> forestMove = std::make_shared<TransMove>(glm::vec3(20.0, -5.0, 20.0));

    /* LIGHTS */
    auto sunLight = std::make_shared<PointLight>(glm::vec3(0.0f, 200.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.75f));
    auto moonLight = std::make_shared<PointLight>(glm::vec3(250.0f, 90.0f, 90.0f), glm::vec3(0.2f, 0.2f, 0.3f));
    auto pureWhiteLight = std::make_shared<PointLight>(glm::vec3(0.0f, 200.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f));
    auto redLight = std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.0f, 0.0f));
    auto dirLight = std::make_shared<DirLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.8f, 0.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
    auto spotLight = std::make_shared<SpotLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-9.0f, 5.0f, 1.0f), 12.5f);
    lights.push_back(sunLight);
    lights.push_back(pureWhiteLight);

    /* COLORS */
    glm::vec3 white {1.0f, 1.0f, 1.0f};
    glm::vec3 purple {0.7f, 0.5f, 0.7f};
    glm::vec3 yellow {1.0f, 1.0f, 0.0f};
    glm::vec3 darkgreen {0.2f, 0.4f, 0.2f};

    /* SHADERS */
    std::shared_ptr<Shader> floorShader = std::make_shared<Shader>("floor.vsh", "floor.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> basicLightShader = std::make_shared<Shader>("base.vsh", "light.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> hezkeKouleShader = std::make_shared<Shader>("base.vsh", "4_hezke_koule.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> treeShader = std::make_shared<Shader>("treeShader.vsh", "treeShader.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> gouraudShader = std::make_shared<Shader>("gouraud.vsh", "gouraud.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> multilightShader = std::make_shared<Shader>("multilight.vsh", "multilight.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight, moonLight}, false);
    std::shared_ptr<Shader> texturedLightShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight}, false);
    std::shared_ptr<Shader> skyBoxShader = std::make_shared<Shader>("skybox.vsh", "skybox.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight}, true);

    /* MODELS */
    std::shared_ptr<Model> treeModel = std::make_shared<Model>(tree, GL_TRIANGLES, 92814, 3, 3, 3, 6);
    std::shared_ptr<Model> bushModel = std::make_shared<Model>(bush, GL_TRIANGLES, 8730, 3, 3, 3, 6);
    std::shared_ptr<Model> sphereModel = std::make_shared<Model>(sphere, GL_TRIANGLES, 2880, 3, 3, 3, 6);
    std::shared_ptr<Model> cubeModel = std::make_shared<Model>(cube, GL_TRIANGLES, 36, 3, 2, 3, 5);

    /* OBJECTS */
    glDepthMask(GL_FALSE);
    addObjectToScene(
            std::make_shared<Object>(cubeModel, white))
            ->linkShader(skyBoxShader);
    glDepthMask(GL_TRUE);

    addObjectToScene(
            std::make_shared<Object>("model.obj", white))
                    ->linkShader(texturedLightShader);

    addObjectToScene(
            std::make_shared<Object>(floor_model, GL_POLYGON, 4, 4, 4, 4, 8, glm::vec3(0)))
                ->linkShader(floorShader);
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(basicLightShader)
                ->add(baseOrbit)
                ->add(std::make_shared<TransRotate>(2.5f, -glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 5.0f)))
                ->add(std::make_shared<TransScale>(0.6f));
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(multilightShader)
                ->add(baseOrbit)
                ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(5.0f, 0.0f, 5.0f)))
                ->add(std::make_shared<TransScale>(0.3f));
    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
                ->linkShader(multilightShader)->add(baseOrbit);
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(hezkeKouleShader)
                ->add(pohnoutKoulema)
                ->add(std::make_shared<TransMove>(glm::vec3(3.0, 0.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(hezkeKouleShader)
                ->add(pohnoutKoulema)
                ->add(std::make_shared<TransMove>(glm::vec3(-3.0, 0.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(multilightShader)
                ->add(pohnoutKoulema)
                ->add(std::make_shared<TransMove>(glm::vec3(0.0, 3.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
                ->linkShader(hezkeKouleShader)
                ->add(pohnoutKoulema)
                ->add(std::make_shared<TransMove>(glm::vec3(0.0, -3.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(gift, GL_TRIANGLES, 66624, 3, 3, 3, 6, purple))
                ->linkShader(gouraudShader)
                ->add(forestMove)
                ->add(std::make_shared<TransMove>(glm::vec3(2.0f, 0.0f, -4.0f)))
                ->add(std::make_shared<TransScale>(5.0f));

    for (size_t i = 0; i < 70; ++i){
        addObjectToScene(
                std::make_shared<Object>(treeModel, darkgreen))
                    ->linkShader(multilightShader)
                    ->add(forestMove)
                    ->add(std::make_shared<TransMove>(glm::vec3(rand() % 70, 0.0, rand() % 60)))
                    ->add(std::make_shared<TransScale>(1.0f + (rand() % 5) * 0.08))
                    ->add(std::make_shared<TransRotate>(true, rand() % 120, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    for (size_t i = 0; i < 100; ++i){
        addObjectToScene(
                std::make_shared<Object>(bushModel, darkgreen))
                    ->linkShader(treeShader)
                    ->add(forestMove)
                    ->add(std::make_shared<TransMove>(glm::vec3(rand() % 70  + (rand() % 50 * 0.1), 0.0, rand() % 60  + (rand() % 50 * 0.1))))
                    ->add(std::make_shared<TransRotate>(true, rand() % 120, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
            ->linkShader(multilightShader)
            ->add(std::make_shared<TransMove>(glm::vec3(-10.0, 5.0, 0.0)));


    this->hud = std::make_unique<Hud>();
}

std::shared_ptr<Object> Scene::addObjectToScene(std::shared_ptr<Object> object){
    this->objects.push_back(object);
    return object;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}

