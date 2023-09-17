#include "window.h"

#include "events/keyboard.h"

namespace wind {
    namespace system {
        Window::Window(void (*buildConfig)(WindowConfig*)) {
            WindowConfig config;
            buildConfig(&config);

            glfwWindowHint(GLFW_RESIZABLE, config.resizable);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.opengl_version.x);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.opengl_version.y);
            m_window = glfwCreateWindow(
                config.size.x, config.size.y,
                config.title.c_str(),
                config.fullscreen ? glfwGetPrimaryMonitor() : NULL,
                NULL
            );

            if (!m_window) {
                log().error() << "Fail create window: " << getGLFWError();
                return;
            }

            glfwSetWindowUserPointer(m_window, this);
            close_event = config.close_event;
            
            glfwMakeContextCurrent(m_window);
            glfwSwapInterval(1);

            glfwSetWindowCloseCallback(m_window, closeCallback);
            glfwSetKeyCallback(m_window, _internal::KeyEventHandler::keyCallback);
        
            m_size = config.size;
        }

        Window::~Window() {
            if (!m_window)
                return;
            glfwDestroyWindow(m_window);
        }

        void Window::show() {
            if (!m_window)
                return;
            glfwSwapBuffers(m_window);
        }

        ivec2 Window::size() {
            return m_size;
        }

        void Window::closeCallback(GLFWwindow* gl_window) {
            auto window = (Window*)glfwGetWindowUserPointer(gl_window);
            if (window->close_event)
                window->close_event();
        }
    }
}