//
// Created by daniel on 1.12.22.
//
#include "../../include/scenes/BallScene.h"
#include "../../models/sphere.h"
#include "../../models/floor.h"

BallScene::BallScene(std::shared_ptr<Window> t_window, int width, int height) : Scene(t_window, width, height) {
    glm::vec3 white {1.0f, 1.0f, 1.0f};
    auto sunLight = std::make_shared<PointLight>(glm::vec3(90.0f, 20.0f, 40.0f), glm::vec3(0.8f, 0.8f, 0.75f));

    std::shared_ptr<Shader> hezkeKouleShader = std::make_shared<Shader>("base.vsh", "4_hezke_koule.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> floorShader = std::make_shared<Shader>("floor.vsh", "floor.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);

    std::shared_ptr<TransMove> floorMe = std::make_shared<TransMove>(glm::vec3(0.0, 5.0, 0.0));


    std::shared_ptr<Composite> pohnoutKoulema = std::make_shared<TransMove>(glm::vec3(90.0f, 20.0f, 40.0f));
    std::shared_ptr<Model> sphereModel = std::make_shared<Model>(sphere, GL_TRIANGLES, 2880, 3, 3, 3, 6);

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

    this->hud = std::make_unique<Hud>();

}