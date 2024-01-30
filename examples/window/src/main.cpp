#include "window/events/keyboard.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <utils/utils.h>
#include <window/window.h>

int main() {
    using namespace wind::math;

    wind::Window w([](wind::Window::Config *self) {
        self->title = "Hello, World!";
        self->fullscreen = false;
    });

    while (w.update()) {
        if (wind::Keyboard::isKeyDown(GLFW_KEY_ESCAPE))
            w.close();

        w.show();
    }

    return EXIT_SUCCESS;
}