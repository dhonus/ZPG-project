//
// Created by daniel on 1.12.22.
//
#include "../../include/scenes/OpenWorldScene.h"
#include "../../models/sphere.h"
#include "../../models/suzi_smooth.h"
#include "../../models/suzi_flat.h"
#include "../../models/floor.h"
#include "../../models/bush.h"
#include "../../models/gift.h"
#include "../../models/cube.h"

OpenWorldScene::OpenWorldScene(std::shared_ptr<Window> t_window, int width, int height) : Scene(t_window, width, height) {
    /* TRANSFORMATIONS */
    std::shared_ptr<Composite> baseOrbit = std::make_shared<Trans>();
    std::shared_ptr<Composite> pohnoutKoulema = std::make_shared<Trans>();
    baseOrbit->add(std::make_shared<TransMove>(glm::vec3(80.0, 20.0, 20.0)));
    baseOrbit->add(std::make_shared<TransRotate>(true, 180, glm::vec3(0.0f, 0.0f, .0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    baseOrbit ->add(std::make_shared<TransMove>(glm::vec3{0.0f, 2.0f, 2.0f}))->add(std::make_shared<TransRotate>(0.5f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)))->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(5.0f, 5.0f, 0.0f)));
    pohnoutKoulema->add(std::make_shared<TransMove>(glm::vec3{15.0f, 15.0f, 0.0f}));
    std::shared_ptr<TransMove> forestMove = std::make_shared<TransMove>(glm::vec3(20.0, -5.0, 20.0));
    std::shared_ptr<TransMove> floorMe = std::make_shared<TransMove>(glm::vec3(0.0, 5.0, 0.0));

    /* LIGHTS */
    auto sunLight = std::make_shared<PointLight>(glm::vec3(100.0f, 10.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.75f));
    std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-9.0f, 5.0f, 1.0f), 12.5f);
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
    std::shared_ptr<Shader> floorShader = std::make_shared<Shader>("floor.vsh", "floor.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> hezkeKouleShader = std::make_shared<Shader>("base.vsh", "4_hezke_koule.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> treeShader = std::make_shared<Shader>("treeShader.vsh", "treeShader.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> gouraudShader = std::make_shared<Shader>("gouraud.vsh", "gouraud.fsh", camera, std::vector<std::shared_ptr<Light>>{sunLight}, false);
    std::shared_ptr<Shader> multilightShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false);
    std::shared_ptr<Shader> skyBoxShader = std::make_shared<Shader>("skybox.vsh", "skybox.fsh", camera, std::vector<std::shared_ptr<Light>>{pureWhiteLight}, true);

    std::shared_ptr<Shader> texturedLightShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{ spotLight }, false);
    std::shared_ptr<Shader> normalMapShader = std::make_shared<Shader>("normal_mapping.vsh", "normal_mapping.fsh", camera, std::vector<std::shared_ptr<Light>>{ spotLight, redLight }, false);
    std::shared_ptr<Shader> worldShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false);
    std::shared_ptr<Shader> roadsShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false);
    std::shared_ptr<Shader> cliffsShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, std::vector<std::shared_ptr<Light>>{spotLight}, false);
    treesShader = std::make_shared<Shader>("textured_light.vsh", "textured_light.fsh", camera, lights, false);

    /* MODELS */
    std::shared_ptr<Model> sphereModel = std::make_shared<Model>(sphere, GL_TRIANGLES, 2880, 3, 3, 3, 6);
    std::shared_ptr<Model> cubeModel = std::make_shared<Model>(cube, GL_TRIANGLES, 36, 3, 2, 3, 5);
    std::shared_ptr<Model> houseModel = std::make_shared<Model>("model.obj");
    std::shared_ptr<Model> roadsModel = std::make_shared<Model>("world/roads.obj");
    std::shared_ptr<Model> worldModel = std::make_shared<Model>("world/world.obj");
    std::shared_ptr<Model> havenModel = std::make_shared<Model>("world/haven.obj");
    std::shared_ptr<Model> cliffsModel = std::make_shared<Model>("world/cliffs.obj");
    std::shared_ptr<Model> boxModel = std::make_shared<Model>("normal_map_box/model.obj");

    /* TEXTURES */
    std::shared_ptr<Texture> houseTexture = std::make_shared<Texture>(false, "textures/house.png");
    std::shared_ptr<Texture> skyTexture = std::make_shared<Texture>(true, "");
    std::shared_ptr<Texture> worldTexture = std::make_shared<Texture>(false, "textures/TerrainTexture.png");
    std::shared_ptr<Texture> roadTexture = std::make_shared<Texture>(false, "textures/world/Path.png");
    std::shared_ptr<Texture> cliffTexture = std::make_shared<Texture>(false, "textures/world/Rock.png");
    std::shared_ptr<Texture> normalMappingBaseTexture = std::make_shared<Texture>(false, "textures/normal_map_box/albedo.png");
    std::shared_ptr<Texture> normalMappingNMTexture = std::make_shared<Texture>(false, "textures/normal_map_box/normalmap.png");

    /* OBJECTS */
    glDepthMask(GL_FALSE);
    addObjectToScene(
            std::make_shared<Object>(cubeModel, white))
            ->linkTexture(skyTexture)
            ->linkShader(skyBoxShader);
    glDepthMask(GL_TRUE);

    addObjectToScene(
            std::make_shared<Object>(houseModel, white))
            ->linkShader(texturedLightShader)
            ->linkTexture(houseTexture)
            ->add(std::make_shared<TransMove>(glm::vec3(31.0, 5.7, 28.0)))
            ->add(std::make_shared<TransRotate>(true, 1.4f, -glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 30.0f, 0.0f)));
    addObjectToScene(
            std::make_shared<Object>(worldModel, white))
            ->linkTexture(worldTexture)
            ->linkShader(worldShader);

    addObjectToScene(
            std::make_shared<Object>(roadsModel, black))
            ->linkTexture(roadTexture)
            ->linkShader(roadsShader);
    addObjectToScene(
            std::make_shared<Object>(havenModel, white))
            ->linkShader(treeShader)
            ->add(std::make_shared<TransMove>(glm::vec3(10.0, -2, -6.0)));
    addObjectToScene(
            std::make_shared<Object>(cliffsModel, white))
            ->linkTexture(cliffTexture)
            ->linkShader(cliffsShader);
    addObjectToScene(
            std::make_shared<Object>(floor_model, GL_POLYGON, 4, 4, 4, 4, 8, glm::vec3(0)))
            ->linkShader(floorShader)
            ->add(floorMe);
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
            ->add(std::make_shared<TransMove>(glm::vec3(-50.0, 120.0, 100.0)))
            ->add(std::make_shared<TransRotate>(0.5f, -glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(5.0f, 0.0f, 5.0f)))
            ->add(std::make_shared<TransScale>(40.0f));

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

    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
            ->linkShader(multilightShader)
            ->add(std::make_shared<TransMove>(glm::vec3(60.0, 20.0, 20.0)))
            ->add(std::make_shared<TransParMove>(
                    glm::mat4(
                            glm::vec4(-1.0, 3.0, -3.0, 1.0),
                            glm::vec4(3.0, -6.0, 3.0, 0),
                            glm::vec4(-3.0, 3.0, 0, 0),
                            glm::vec4(1, 0, 0, 0)),
                    glm::mat4x3(
                            glm::vec3(0, 0, 0),
                            glm::vec3(2, 2, 0),
                            glm::vec3(4, 4, 0),
                            glm::vec3(6, 0, 0)),
                    0.5f, false));

    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
            ->linkShader(multilightShader)
            ->add(std::make_shared<TransMove>(glm::vec3(60.0, 20.0, 20.0)))
            ->add(std::make_shared<TransParMove>(
                    glm::mat4(
                            glm::vec4(-1.0, 3.0, -3.0, 1.0),
                            glm::vec4(3.0, -6.0, 3.0, 0),
                            glm::vec4(-3.0, 3.0, 0, 0),
                            glm::vec4(1, 0, 0, 0)),
                    glm::mat4x3(
                            glm::vec3(0, 0, 0),
                            glm::vec3(2, 2, 0),
                            glm::vec3(4, 4, 0),
                            glm::vec3(6, 0, 0)),
                    0.5f, true));

    addObjectToScene(
            std::make_shared<Object>(boxModel, white))
            ->linkShader(normalMapShader)
            ->linkTexture(normalMappingBaseTexture)
            ->linkTexture(normalMappingNMTexture)
            ->add(std::make_shared<TransMove>(glm::vec3(100.0, 20.0, 40.0)));

    addObjectToScene(
            std::make_shared<Object>(suziFlat, GL_TRIANGLES, 2904, 3, 3, 3, 6, white))
            ->linkShader(multilightShader)
            ->add(std::make_shared<TransMove>(glm::vec3(10.0, -2, -6.0)));

    addObjectToScene(
            std::make_shared<Object>(std::make_shared<Model>("nmap/sphere/model.obj"), white))
            ->linkShader(normalMapShader)
            ->linkTexture(std::make_shared<Texture>(false, "textures/sphere/albedo.png"))
            ->linkTexture(std::make_shared<Texture>(false, "textures/sphere/normalmap.png"))
            ->add(std::make_shared<TransMove>(glm::vec3(100.0, 10.0, 40.0)));

    this->hud = std::make_unique<Hud>();
}