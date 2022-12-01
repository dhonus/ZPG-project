//
// Created by daniel on 1.12.22.
//
#include "../../include/scenes/BallScene.h"
#include "../../models/sphere.h"
#include "../../models/floor.h"
#include "../../models/gift.h"

BallScene::BallScene(std::shared_ptr<Window> t_window, int width, int height) : Scene(t_window, width, height) {
    /* COLORS */
    glm::vec3 white {1.0f, 1.0f, 1.0f};
    glm::vec3 purple {0.7f, 0.5f, 0.7f};

    /* LIGHTS */
    auto sunLight = std::make_shared<PointLight>(glm::vec3(90.0f, 20.0f, 40.0f), glm::vec3(0.8f, 0.8f, 0.75f));

    /* SHADERS */
    auto hezkeKouleShader = std::make_shared<Shader>("base.vsh", "4_hezke_koule.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    auto floorShader = std::make_shared<Shader>("floor.vsh", "floor.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    auto gouraudShader = std::make_shared<Shader>("gouraud.vsh", "gouraud.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);

    /* TRANSFORMATIONS */
    auto floorMe = std::make_shared<TransMove>(glm::vec3(0.0, 5.0, 0.0));
    auto pohnoutKoulema = std::make_shared<TransMove>(glm::vec3(90.0f, 20.0f, 40.0f));
    auto moveMe = std::make_shared<TransMove>(glm::vec3(90.0f, 0.0f, 40.0f));
    auto sphereModel = std::make_shared<Model>(sphere, GL_TRIANGLES, 2880, 3, 3, 3, 6);

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
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(0.0, 3.0, 0.0)));
    addObjectToScene(
            std::make_shared<Object>(sphereModel, white))
            ->linkShader(hezkeKouleShader)
            ->add(pohnoutKoulema)
            ->add(std::make_shared<TransMove>(glm::vec3(0.0, -3.0, 0.0)));

    addObjectToScene(
            std::make_shared<Object>(floor_model, GL_POLYGON, 4, 4, 4, 4, 8, glm::vec3(0)))
            ->linkShader(floorShader)
            ->add(floorMe);

    addObjectToScene(
            std::make_shared<Object>(gift, GL_TRIANGLES, 66624, 3, 3, 3, 6, purple))
            ->linkShader(gouraudShader)
            ->add(moveMe)
            ->add(std::make_shared<TransScale>(5.0f));

    this->hud = std::make_unique<Hud>();

}