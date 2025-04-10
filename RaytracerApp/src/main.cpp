#include "application.hpp"
#include "entry.hpp"
#include "timer.hpp"

#include "renderer.hpp"
#include "camera.hpp"

#include <glm/gtc/type_ptr.hpp>

using namespace BaseEngine;

class RenderLayer : public Layer {
    public:
        RenderLayer() : cam(45.0f, 0.1f, 100.0f) {

            Material& pink = scene.Materials.emplace_back();
            pink.albedo = { 1.0f, 0.0f, 1.0f };
            pink.roughness = 0.0f;

            Material& blue = scene.Materials.emplace_back();
            blue.albedo = { 0.2f, 0.3f, 1.0f };
            blue.roughness = 0.1f;

            {
                Sphere sphere;
                sphere.pos = glm::vec3(-0.5f, 0.0f, 0.0f);
                // sphere.radius = 0.5;
                // sphere.albedo = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
                sphere.radius = 1.0f;
                sphere.mat_idx = 0;

                scene.Spheres.push_back(sphere);
            }

            {
                Sphere sphere;
                // sphere.pos = glm::vec3(1.0f, 0.0f, -5.0f);
                // sphere.radius = 0.5f;
                // sphere.albedo = glm::vec3(0.0f, 0.0f, 1.0f);

                sphere.pos = glm::vec3(0.0f, -101.0f, 0.0f);
                sphere.radius = 100.0f;
                sphere.mat_idx = 1;
                scene.Spheres.push_back(sphere);
            }
        }

        virtual void onUpdate(float ts) override {
            cam.onUpdate(ts);
        }

        virtual void onUIRender() override {
            // Panel for general raytracer settings
            ImGui::Begin("Settings");
                ImGui::Text("Render time: %.3fms", renderTime);
                if (ImGui::Button("Render")) {
                    render();
                }

                ImGui::DragInt("Bounces", &scene.bounces, 1, 1, INT_MAX); // id, data, step, min, max

                ImGui::ColorPicker3("Background Color", glm::value_ptr(scene.background));

            ImGui::End();

            // Panel for Scene Layout
            ImGui::Begin("Scene");

                if (ImGui::Button("Add Shape")) {
                    showAddShape = true;
                }

                ImGui::Separator();

                for (size_t i = 0; i < scene.Spheres.size(); i++) {
                    ImGui::PushID(i);

                        Sphere& sp = scene.Spheres[i];
                        ImGui::DragFloat3("Position", glm::value_ptr(sp.pos), 0.1f);
                        ImGui::DragFloat("Radius", &sp.radius, 0.1f);
                        ImGui::DragInt("Material", &sp.mat_idx, 1.0f, 0, (int) scene.Materials.size() - 1);

                        ImGui::Separator();

                    ImGui::PopID();
                }

                if (ImGui::Button("Add Material")) {
                    showAddMaterial = true;
                }

                ImGui::Separator();

                for (size_t i = 0; i < scene.Materials.size(); i++) {
                    ImGui::PushID(i);

                        Material& m = scene.Materials[i];
                        ImGui::ColorEdit3("Albedo", glm::value_ptr(m.albedo));
                        ImGui::DragFloat("Roughness", &m.roughness, 0.05f, 0.0f, 1.0f);
                        ImGui::DragFloat("Metallic", &m.metallic, 0.05f, 0.0f, 1.0f);

                        ImGui::Separator();

                    ImGui::PopID();
                }

            ImGui::End();

            // Panel for viewing raytracer output
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Viewport");
                vp_wd = ImGui::GetContentRegionAvail().x;
                vp_ht = ImGui::GetContentRegionAvail().y;

                auto img = renderer.getFinalImg();

                if (img) {
                    ImGui::Image((ImTextureID)img->getDescriptorSet(),
                            {
                                (float) img->getWd(),
                                (float) img->getHt()
                            },
                            ImVec2(0, 1), ImVec2(1, 0)
                );

            }

            ImGui::End();
            ImGui::PopStyleVar();

            // Create new shape window (when pressed)
            if (showAddShape) {
                ImGui::SetNextWindowSize(ImVec2(300, 350), ImGuiCond_Appearing);
                ImGui::Begin("New Shape Configuration");

                        static Sphere sp_tmp;
                        static bool tempSphereAdded = false;

                        if (!tempSphereAdded) {
                            scene.Spheres.push_back(sp_tmp);
                            tempSphereAdded = true;
                        }

                        Sphere& sp = scene.Spheres.back();
                        ImGui::DragFloat3("Position", glm::value_ptr(sp.pos), 0.1f);
                        ImGui::DragFloat("Radius", &sp.radius);
                        // ImGui::ColorPicker3("Albedo", glm::value_ptr(sp.albedo));
                        ImGui::DragInt("Material", &sp.mat_idx, 1.0f, 0, (int) scene.Materials.size() - 1);

                        if (ImGui::Button("Confirm")) {
                            showAddShape = false;
                            tempSphereAdded = false;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Exit")) {
                            scene.Spheres.pop_back();
                            showAddShape = false;
                            tempSphereAdded = false;
                        }

                ImGui::End();
            }

            // Create new window (when pressed) to create new material
            if (showAddMaterial) {
                ImGui::SetNextWindowSize(ImVec2(300, 350), ImGuiCond_Appearing);
                ImGui::Begin("New Material Configuration");

                    static Material m_tmp;
                    static bool tmpMAdded = false;

                    if (!tmpMAdded) {
                        scene.Materials.push_back(m_tmp);
                        tmpMAdded = true;
                    }

                    Material& m = scene.Materials.back();
                    ImGui::ColorPicker3("Albedo", glm::value_ptr(m.albedo));
                    ImGui::DragFloat("Roughness", &m.roughness, 0.05f, 0.0f, 1.0f);
                    ImGui::DragFloat("Metallic", &m.metallic, 0.05f, 0.0f, 1.0f);

                    if (ImGui::Button("Confirm")) {
                        showAddMaterial = false;
                        tmpMAdded = false;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Exit")) {
                        scene.Materials.pop_back();
                        showAddMaterial = false;
                        tmpMAdded = false;
                    }

                ImGui::End();
            }

            render();
        }

        void render() {
            Timer timer;

            renderer.onResize(vp_wd, vp_ht);
            cam.onResize(vp_wd, vp_ht);
            renderer.render(scene, cam);

            renderTime = timer.elapsedMillis();
        }

    private:
        Renderer renderer;
        Camera cam;
        Scene scene;
    uint32_t* img_data = nullptr;
        uint32_t vp_wd = 0, vp_ht = 0;
        float renderTime = 0;

        bool showAddShape = false;
        bool showAddMaterial = false;
};

BaseEngine::Application* BaseEngine::createApplicaion(int argc, char** argv) {
    ApplicationSpecification spec;
    spec.name = "Raytracer";

    Application* app = new BaseEngine::Application(spec);
    app->pushLayer<RenderLayer>();
    app->setMenubarCallback([app]() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                app->close();
            }
            ImGui::EndMenu();
        }
    });


    return app;
}
