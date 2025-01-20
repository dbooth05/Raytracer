#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "constants.hpp"

class Camera {
    public:
        Camera() : pos(10.0f, 10.0f, 10.0f),
                   lookAt(0.0f, 0.0f, 0.0f),
                   up(0.0f, 1.0f, 0.0f),
                   fov(45.0f),
                   aspect(16.0f / 9.0f),
                   aliasing(1)
        {
            bg[0] = bg[1] = 0.1f; bg[2] = 0.2f; bg[3] = 1.0f;
        }

        // Setter functions
        void setPos(const glm::vec3& pos) { this->pos = pos; }
        void setLookAt(const glm::vec3& lookAt) { this->lookAt = lookAt; }
        void setFOV(float fov) { this->fov = fov; }
        void setAspect(float aspect) { this->aspect = aspect; }
        void setBgCol(float r, float g, float b, float a) {
            bg[0] = r; bg[1] = g; bg[2] = b; bg[3] = a;
        }

        // Getter functions
        glm::mat4 getViewMatrix() const { return glm::lookAt(pos, lookAt, up); }

        glm::mat4 getProjectionMatrix() const {
            return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
        }

        const float* getBgColor() const { return bg; }

        // Display Camera Settings
        void cameraSettings() {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.15f, 0.7f));
            ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Always);
            ImGui::Begin("Camera Settings", nullptr, ImGuiWindowFlags_NoResize);
            {   // Camera Position
                    if (ImGui::CollapsingHeader("Position")) {
                        ImGui::SliderFloat("x:", &pos.x, -1000, 1000);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", pos.x);

                        ImGui::SliderFloat("y:", &pos.y, -1000, 1000);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", pos.y);

                        ImGui::SliderFloat("z:", &pos.z, -1000, 1000);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", pos.z);
                    }
            }
            
            {   // Camera Look At Position
                    if (ImGui::CollapsingHeader("Look At")) {
                        ImGui::SliderFloat("#x:", &lookAt.x, -100, 100);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", lookAt.x);

                        ImGui::SliderFloat("#y:", &lookAt.y, -100, 100);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", lookAt.y);

                        ImGui::SliderFloat("#z:", &lookAt.z, -100, 100);
                        ImGui::SameLine();
                        ImGui::Text("%.2f", lookAt.z);
                    }
            } 

            {   // Background
                if (ImGui::CollapsingHeader("Background")) {
                    ImGui::ColorPicker4("bg-col", bg);
                }
            }

            ImGui::End();
            ImGui::PopStyleColor();
        }

    public:
        glm::vec3 pos;
        glm::vec3 lookAt;
        glm::vec3 up;
        
        float fov;
        float aspect;
        int aliasing;
        float bg[4];
};

#endif