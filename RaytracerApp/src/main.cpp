#include "application.hpp"
#include "entry.hpp"
#include "image.hpp"
#include "timer.hpp"
#include "random.hpp"

#include <iostream>

using namespace BaseEngine;

class RenderLayer : public Layer {
    public:
        virtual void onUIRender() override {
            ImGui::Begin("Settings");
                ImGui::Text("Render time: %.3f milliseconds", renderTime);
                if (ImGui::Button("Render")) {
                    render();
                }

            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Viewport");

            vp_wd = ImGui::GetContentRegionAvail().x;
            vp_ht = ImGui::GetContentRegionAvail().y;

            if (m_Image) {
                ImGui::Image((ImTextureID)m_Image->getDescriptorSet(),
                            {
                                (float) m_Image->getWd(),
                                (float) m_Image->getHt()
                            });

            }

            ImGui::End();
            ImGui::PopStyleVar();
        }

        void render() {
            Timer timer;

            if (!m_Image || vp_wd != m_Image->getWd() || vp_ht != m_Image->getHt()) {

                m_Image = std::make_shared<Image>(vp_wd, vp_ht, ImageFormat::RGBA);
                delete[] img_data;
                img_data = new uint32_t[vp_wd * vp_ht];
            }

            for (uint32_t i = 0; i < vp_wd * vp_ht; i++) {
                img_data[i] = Random::UInt();
                img_data[i] |= 0xff000000;
            }

            m_Image->setData(img_data);

            renderTime = timer.elapsedMillis();
        }

    private:
        std::shared_ptr<Image> m_Image;
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
