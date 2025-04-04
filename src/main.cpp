#include "application.hpp"
#include "layer.hpp"
#include "image.hpp"

class RenderLayer : public BaseEngine::Layer {
    public:
        virtual void onUIRender() override {

        }
};

BaseEngine::Application* BaseEngine::createApplicaion(int argc, char** argv) {
    BaseEngine::ApplicationSpecification spec;
    spec.name = "Raytracer";

    BaseEngine::Application* app = new BaseEngine::Application(spec);
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
