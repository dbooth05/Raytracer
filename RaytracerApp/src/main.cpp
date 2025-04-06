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
            Sphere sphere;
            sphere.pos = glm::vec3(-0.5f, 0.0f, 0.0f);
            sphere.radius = 0.5;
            sphere.albedo = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

            scene.Spheres.push_back(sphere);
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

            ImGui::End();

            // Panel for Scene Layout
            ImGui::Begin("Scene");
                for (size_t i = 0; i < scene.Spheres.size(); i++) {
                    ImGui::PushID(i);

                        Sphere& sp = scene.Spheres[i];
                        ImGui::DragFloat3("Position", glm::value_ptr(sp.pos), 0.1f);
                        ImGui::DragFloat("Radius", &sp.radius, 0.1f);
                        ImGui::ColorEdit3("Albedo", glm::value_ptr(sp.albedo));

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
