//
// Created by daniel on 26.9.22.
//

#include "../include/Scene.h"


int Scene::render() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->immutable_objects = this->object_id;

    while (!glfwWindowShouldClose(window->getWindow())) {
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // This makes the movement with WASD immediate.
        // A callback is unusable for this.
        camera->move(
                glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS,
                glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS,
                glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS,
                glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS,
                glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS,
                glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

        for (auto &o: this->objects) {
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
}

std::shared_ptr<Object> Scene::addObjectToScene(std::shared_ptr<Object> object) {
    object->setID(object_id++);
    this->objects.push_back(object);
    return object;
}

Scene::~Scene() {
    delete this->camera;
    delete this->callbacks;
}

void Scene::update(Subject &s) {
    if (&s == callbacks) {
        auto pos = callbacks->clickedPosition;
        auto index = callbacks->clickedId;
        if (index > immutable_objects) {
            // find in vector
            for (auto &o: this->objects) {
                if (o->getID() == index) {
                    // remove from vector
                    this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), o),
                                        this->objects.end());
                    break;
                }
            }
            return;
        }
        std::cout << "[OK] Planting a tree at " << pos.x << " " << pos.y << " " << pos.z << std::endl;
        addObjectToScene(
                std::make_shared<Object>("trees/tree/tree.obj", glm::vec3{0.2f, 0.2f, 0.2f}))
                ->linkShader(treesShader)
                ->linkTexture(std::make_shared<Texture>(false, "textures/tree.png"))
                ->add(std::make_shared<TransMove>(pos))
                ->add(std::make_shared<TransRotate>(true, rand() % 120, glm::vec3(0.0f, 0.0f, .0f),
                                                    glm::vec3(0.0f, 1.0f, 0.0f)))
                ->add(std::make_shared<TransScale>(((rand() % 2 + 1) * 0.15)));
    }
}