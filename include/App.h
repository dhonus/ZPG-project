//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_APP_H
#define OGL_TST_02_APP_H
#include <memory>
#include "Callbacks.h"

class App {
public:
    App();
    ~App() = default;
    int init();
private:
    std::shared_ptr<Window> window;
    std::shared_ptr<Scene> scene;
};


#endif //OGL_TST_02_APP_H
