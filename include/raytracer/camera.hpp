#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "imgui/imgui.h"
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vec3.hpp"

class Camera {
    public:
        Camera(float x, float y, float z, float fov = 90.0f, float aspect = 1.33f)
        : fov(fov), aspect(aspect) {
            pos     = vec3(x, y, z);
            forward = vec3(0.0f, 0.0f, -1.0f);
            up      = vec3(0.0f, 1.0f, 0.0f);
            right   = vec3(1.0f, 0.0f, 0.0f);
        }

        void UpdatePos(const vec3& newPos) {
            pos = newPos;
        }

        void SetViewDir(const vec3& dir) {
            forward = dir;
            // normalize the forward vector
        }

        void RenderUI() {
            ImGui::Text("Camera Position");
            ImGui::DragFloat3("Position", &pos.x, 0.1f, -100.0f, 100.0f);

            ImGui::Text("Camera View Direction");
            ImGui::DragFloat3("Forward", &forward.x, 0.1f, -1.0f, 1.0f);
        }

        const vec3& GetPos() const { return pos; }
        const vec3& GetForward() const { return forward; }

    private:
        vec3 pos;
        vec3 forward;
        vec3 up;
        vec3 right;

        float fov;
        float aspect;
};

#endif