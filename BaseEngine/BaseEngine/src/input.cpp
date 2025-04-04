#include "input/input.hpp"

#include "application.hpp"

#include <GLFW/glfw3.h>

namespace BaseEngine {

    bool Input::isKeyDown(KeyCode kc) {
        GLFWwindow* windowHandle = Application::get().getWindowHandle();
        int state = glfwGetKey(windowHandle, (int) kc);
        return state == GLFW_PRESS;
    }

    bool Input::isMouseButtonDown(MouseButton b) {
        GLFWwindow* windowHandle = Application::get().getWindowHandle();
        int state = glfwGetMouseButton(windowHandle, (int) b);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePos() {
        GLFWwindow* windowHandle = Application::get().getWindowHandle();

        double x, y;
        glfwGetCursorPos(windowHandle, &x, &y);
        return { (float) x, (float) y };
    }

    void Input::setCursorMode(CursorMode mode) {
        GLFWwindow* windowHandle = Application::get().getWindowHandle();
        glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int) mode);
    }
};
