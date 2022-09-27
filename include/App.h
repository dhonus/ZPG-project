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
    Shader* shader;
    void error_check();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void window_focus_callback(GLFWwindow *window, int focused);

    void window_iconify_callback(GLFWwindow *window, int iconified);

    void window_size_callback(GLFWwindow *window, int width, int height);

    void cursor_callback(GLFWwindow *window, double x, double y);

    void button_callback(GLFWwindow *window, int button, int action, int mode);
};


#endif //OGL_TST_02_APP_H
