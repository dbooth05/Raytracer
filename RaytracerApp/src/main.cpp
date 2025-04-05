#include "application.hpp"
#include "entry.hpp"
#include "timer.hpp"

#include "camera.hpp"

using namespace BaseEngine;

class RenderLayer : public Layer {
    public:
        virtual void onUIRender() override {
            ImGui::Begin("Settings");
                ImGui::Text("Render time: %.3fms", renderTime);
                if (ImGui::Button("Render")) {
                    render();
                }

            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Viewport");

            vp_wd = ImGui::GetContentRegionAvail().x;
            vp_ht = ImGui::GetContentRegionAvail().y;

            auto img = cam.getFinalImg();

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

            cam.onResize(vp_wd, vp_ht);
            cam.render();

            renderTime = timer.elapsedMillis();
        }

    private:
        Camera cam;
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
