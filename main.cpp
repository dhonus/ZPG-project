#include "include/Window.h"
#include "include/Renderer.h"
#include "include/Shader.h"
#include "include/App.h"

int main(void) {
    App *app = new App();
    app->init();
    delete app;

    return 0;
}
