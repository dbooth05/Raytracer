#ifndef INPUT_H
#define INPUT_H

#include "keyCodes.hpp"

#include <glm/glm.hpp>

namespace BaseEngine {
    class Input {
        public:
            static bool isKeyDown(KeyCode kc);
            static bool isMouseButtonDown(MouseButton button);

            static glm::vec2 getMousePos();

            static void setCursorMode(CursorMode mode);
    };
}

#endif
