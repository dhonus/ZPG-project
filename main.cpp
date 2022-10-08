#include "include/Window.h"
#include "include/Scene.h"
#include "include/Shader.h"
#include "include/App.h"
#include <memory>

int main(void) {
    std::unique_ptr<App> app = std::make_unique<App>();
    app->init();
    return 0;
}
