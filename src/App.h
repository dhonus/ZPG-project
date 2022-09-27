//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_APP_H
#define OGL_TST_02_APP_H


class App {
public:
    App();
    int init();
    int close();
private:
    Renderer* renderer;
    Window* window;
    ShaderObject* shaderObject;
};


#endif //OGL_TST_02_APP_H
