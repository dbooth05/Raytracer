#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "input.hpp" // from BaseEngine

using namespace BaseEngine;

Camera::Camera(float vertFov, float near, float far)
    : vertFov(vertFov), near(near), far(far) {

    forwardDir = glm::vec3(0, 0, -1);
    pos = glm::vec3(0, 0, 6);
}

void Camera::onUpdate(float ts) {
    glm::vec2 mousePos = Input::getMousePos();
    glm::vec2 delta = (mousePos - lastMousePos) * 0.002f; // 0.002 is sensitivity
    lastMousePos = mousePos;

    if (!Input::isMouseButtonDown(MouseButton::RIGHT)) {
        Input::setCursorMode(CursorMode::NORMAL);
        return;
    }

    Input::setCursorMode(CursorMode::LOCKED);

    bool moved = false;

    constexpr glm::vec3 upDir(0.0f, 1.0f, 0.0f); // could be modified to support rotating camera around in angles (i.e. 90 degrees)
    glm::vec3 rightDir = glm::cross(forwardDir, upDir);

    float speed = 5.0f;

    // movement (a,w,s,d)
    if (Input::isKeyDown(KeyCode::W)) {
        pos += forwardDir * speed * ts;
        moved = true;
    } else if (Input::isKeyDown(KeyCode::S)) {
        pos -= forwardDir * speed * ts;
    }

    if (Input::isKeyDown(KeyCode::A)) {
        pos -= rightDir * speed * ts;
        moved = true;
    } else if (Input::isKeyDown(KeyCode::D)) {
        pos += rightDir * speed * ts;
    }

    if (Input::isKeyDown(KeyCode::Q)) {
        pos -= upDir * speed * ts;
        moved = true;
    } else if (Input::isKeyDown(KeyCode::E)) {
        pos += upDir * speed * ts;
        moved = true;
    }

    // rotation
    if (delta.x != 0.0f || delta.y != 0.0f) {
        float pitch = delta.y * getRotationSpeed();
        float yaw = delta.x * getRotationSpeed();

        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitch, rightDir), glm::angleAxis(-yaw, glm::vec3(0.0f, 1.0f, 0.0f))));
        forwardDir = glm::rotate(q, forwardDir);

        moved = true;
    }

    if (moved) {
        recalcView();
        recalcRayDirs();
    }
}

void Camera::onResize(uint32_t wd, uint32_t ht) {
    if (wd == vpWd && ht == vpHt) return;

    vpWd = wd;
    vpHt = ht;

    recalcProj();
    recalcRayDirs();
}

float Camera::getRotationSpeed() {
    return 0.3f;
}

void Camera::recalcProj() {
    proj = glm::perspectiveFov(glm::radians(vertFov), (float) vpWd, (float) vpHt, near, far);
    invProj = glm::inverse(proj);
}

void Camera::recalcView() {
    view = glm::lookAt(pos, pos + forwardDir, glm::vec3(0, 1, 0));
    invView = glm::inverse(view);
}

void Camera::recalcRayDirs() {
    rayDirs.resize(vpWd * vpHt);

    for (uint32_t y = 0; y < vpHt; y++) {
        for (uint32_t x = 0; x < vpWd; x++) {
            glm::vec2 coord = { (float) x / (float) vpWd,
                                (float) y / (float) vpHt };
            coord = coord * 2.0f - 1.0f; // -1 -> 1

            glm::vec4 target = invProj * glm::vec4(coord.x, coord.y, 1, 1);
            glm::vec3 rayDir = glm::vec3(invView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // world space

            rayDirs[x + y * vpWd] = rayDir;
        }
    }
}
