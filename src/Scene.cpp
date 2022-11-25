//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"
#include "../models/sphere.h"
#include "../models/suzi_smooth.h"
#include "../models/suzi_flat.h"
#include "../models/floor.h"
#include "../models/bush.h"
#include "../models/gift.h"
#include "../models/cube.h"

int Scene::render() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while (!glfwWindowShouldClose(window->getWindow())) {
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

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

        for (auto & o : this->objects){
            glStencilFunc(GL_ALWAYS, o->getID(), 0xFF);
            o->draw();
        }

        hud->draw(*camera);

        glfwPollEvents();
        glfwSwapBuffers(window->getWindow());
    }

    return 0;
}

Scene::Scene(std::shared_ptr<Window> t_window, int width, int height) {
    srand(time(NULL));
    glEnable(GL_BLEND);

    /* SCENE SETUP */
    this->window = t_window;
    this->callbacks = new Callbacks(*this->window->getWindow());
    this->camera = new Camera(width, height, *callbacks);
    this->callbacks->setCamera(this->camera);
    this->callbacks->attach(this);
    this->callbacks->attach(this->camera);

    /* TRANSFORMATIONS */
    std::shared_ptr<Composite> baseOrbit = std::make_shared<Trans>();
    std::shared_ptr<Composite> pohnoutKoulema = std::make_shared<Trans>();
    //baseOrbit->add(std::make_shared<TransMove>(glm::vec3(20.0, 0.0, 20.0)));
    baseOrbit->add(std::make_shared<TransMove>(glm::vec3(80.0, 20.0, 20.0)));
    baseOrbit->add(std::make_shared<TransRotate>(true, 180, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    baseOrbit ->add(std::make_shared<TransMove>(glm::vec3{0.0f, 2.0f, 2.0f}))->add(std::make_shared<TransRotate>(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)))->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));
    pohnoutKoulema->add(std::make_shared<TransMove>(glm::vec3{15.0f, 15.0f, 0.0f}));
    std::shared_ptr<TransMove> forestMove = std::make_shared<TransMove>(glm::vec3(20.0, -5.0, 20.0));
    std::shared_ptr<TransMove> floorMe = std::make_shared<TransMove>(glm::vec3(0.0, 5.0, 0.0));

    /* LIGHTS */
    auto sunLight = std::make_shared<PointLight>(glm::vec3(100.0f, 10.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.75f));
    std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-9.0f, 5.0f, 1.0f), 12.5f);
    auto moonLight = std::make_shared<PointLight>(glm::vec3(250.0f, 90.0f, 90.0f), glm::vec3(0.2f, 0.2f, 0.3f));
    auto pureWhiteLight = std::make_shared<PointLight>(glm::vec3(0.0f, 200.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f));
    auto redLight = std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.0f, 0.0f));
    auto dirLight = std::make_shared<DirLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.8f, 0.0f), glm::vec3(-0.2f, -1.0f, -0.3f));
    auto dumbLight = std::make_shared<SpotLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    lights.push_back(sunLight);
    lights.push_back(pureWhiteLight);

    /* COLORS */
    glm::vec3 white {1.0f, 1.0f, 1.0f};
    glm::vec3 black {0.0f, 0.0f, 0.0f};
    glm::vec3 purple {0.7f, 0.5f, 0.7f};
    glm::vec3 yellow {1.0f, 1.0f, 0.0f};
    glm::vec3 darkgreen {0.2f, 0.4f, 0.2f};

    GLuint err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "GL ERROR: " << err << std::endl;
        return;
    }

    /* SHADERS */
    std::shared_ptr<Shader> floorShader = std::make_shared<Shader>("floor.vsh", "floor.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false, "");
    std::shared_ptr<Shader> basicLightShader = std::make_shared<Shader>("base.vsh", "light.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight, sunLight}, false, "");
    std::shared_ptr<Shader> hezkeKouleShader = std::make_shared<Shader>("base.vsh", "4_hezke_koule.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false, "");
    std::shared_ptr<Shader> treeShader = std::make_shared<Shader>("treeShader.vsh", "treeShader.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false, "");
    std::shared_ptr<Shader> gouraudShader = std::make_shared<Shader>("gouraud.vsh", "gouraud.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false, "");
    std::shared_ptr<Shader> multilightShader = std::make_shared<Shader>("multilight.vsh", "multilight.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight, moonLight}, false, "model.png");
    std::shared_ptr<Shader> skyBoxShader = std::make_shared<Shader>("skybox.vsh", "skybox.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight}, true, "");

    std::shared_ptr<Shader> texturedLightShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{ spotLight }, false, "model.png");
    std::shared_ptr<Shader> normalMapShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{ spotLight }, false, "normal_map_box/albedo.png");
    std::shared_ptr<Shader> worldShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false, "TerrainTexture_01.png");
    std::shared_ptr<Shader> roadsShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false, "world/toppng_com-pathway-png-900x225.png");
    std::shared_ptr<Shader> cliffsShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{dumbLight}, false, "world/Rock.png");
//    std::shared_ptr<Shader> crosshairShader = std::make_shared<Shader>("crosshair.vsh", "crosshair.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight}, false, "target_small.png");

    /* MODELS */
    //std::shared_ptr<Model> treeModel = std::make_shared<Model>(tree, GL_TRIANGLES, 92814, 3, 3, 3, 6);
    //std::shared_ptr<Model> bushModel = std::make_shared<Model>(bush, GL_TRIANGLES, 8730, 3, 3, 3, 6);
    std::shared_ptr<Model> sphereModel = std::make_shared<Model>(sphere, GL_TRIANGLES, 2880, 3, 3, 3, 6);
    std::shared_ptr<Model> cubeModel = std::make_shared<Model>(cube, GL_TRIANGLES, 36, 3, 2, 3, 5);
    std::shared_ptr<Model> houseModel = std::make_shared<Model>("model.obj");
    std::shared_ptr<Model> roadsModel = std::make_shared<Model>("world/roads.obj");
    std::shared_ptr<Model> worldModel = std::make_shared<Model>("world/world.obj");
    std::shared_ptr<Model> havenModel = std::make_shared<Model>("world/haven.obj");
    std::shared_ptr<Model> cliffsModel = std::make_shared<Model>("world/cliffs.obj");
    std::shared_ptr<Model> boxModel = std::make_shared<Model>("normal_map_box/model.obj");

    /* OBJECTS */
    glDepthMask(GL_FALSE);
    addObjectToScene(
            std::make_shared<Object>(cubeModel, white))
            ->linkShader(skyBoxShader);
    glDepthMask(GL_TRUE);

    addObjectToScene(
            std::make_shared<Object>(houseModel, white))
                    ->linkShader(texturedLightShader)
                    ->add(std::make_shared<TransMove>(glm::vec3(31.0, 5.7, 28.0)))
                    ->add(std::make_shared<TransRotate>(true, 1.4f, -glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 30.0f, 0.0f)));
    addObjectToScene(
            std::make_shared<Object>(worldModel, white))
            ->linkShader(worldShader);

    addObjectToScene(
            std::make_shared<Object>(roadsModel, black))
            ->linkShader(roadsShader);
    addObjectToScene(
            std::make_shared<Object>(havenModel, white))
            ->linkShader(treeShader)
            ->add(std::make_shared<TransMove>(glm::vec3(10.0, -2, -6.0)));
    addObjectToScene(
            std::make_shared<Object>(cliffsModel, white))
            ->linkShader(cliffsShader);
    addObjectToScene(
            std::make_shared<Object>(floor_model, GL_POLYGON, 4, 4, 4, 4, 8, glm::vec3(0)))
                ->linkShader(floorShader)
                ->add(floorMe);
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

    /*
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
*/
    //glEnable(GL_BLEND); //Enable blending.
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
            ->linkShader(multilightShader)
            ->add(std::make_shared<TransMove>(glm::vec3(-10.0, 50.0, 0.0)));

    addObjectToScene(
            std::make_shared<Object>(boxModel, white))
            ->linkShader(normalMapShader)
            ->add(std::make_shared<TransMove>(glm::vec3(100.0, 20.0, 40.0)));


    /*addObjectToScene(
            std::make_shared<Object>(cubeModel, white))
            ->linkShader(crosshairShader);
    */
    this->hud = std::make_unique<Hud>();
}

std::shared_ptr<Object> Scene::addObjectToScene(std::shared_ptr<Object> object){
    object->setID(object_id++);
    this->objects.push_back(object);
    return object;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}

void Scene::update(Subject &s) {
    if (&s == callbacks){
        std::shared_ptr<Shader> treesShader = std::make_shared<Shader>("multilight.vsh", "multilight.fsh", camera, lights, false, "");

        auto pos = callbacks->clickedPosition;
        std::cout << "Planting a tree at " << pos.x << " " << pos.y << " " << pos.z <<  std::endl;
        addObjectToScene(
                std::make_shared<Object>(std::make_shared<Model>(tree, GL_TRIANGLES, 92814, 3, 3, 3, 6), glm::vec3{0.2f, 0.4f, 0.2f}))
                ->linkShader(treesShader)
                ->add(std::make_shared<TransMove>(pos));
    }
}

