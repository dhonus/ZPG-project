#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Window.h"
#include "../include/Scene.h"
#include "../include/App.h"
#include "../include/scenes/OpenWorldScene.h"
#include "../include/scenes/BallScene.h"

App::App() {
    this->window = std::make_shared<Window>(this->width, this->height);
    glewExperimental = GL_TRUE;
    glewInit();
}

int App::init() {
    //this->scene = std::make_shared<BallScene>(this->window, this->width, this->height);
    this->scene = std::make_shared<OpenWorldScene>(this->window, this->width, this->height);


    this->scene->render();

    return 0;
}
