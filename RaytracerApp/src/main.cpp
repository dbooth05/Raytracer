#include "application.hpp"
#include "entry.hpp"

class ApplicationLayer : public BaseEngine::Layer {
    public:
        virtual void onUIRender() override {
            ImGui::Begin("Hello");
            ImGui::End();
        }
};

BaseEngine::Application* BaseEngine::createApplicaion(int arc, char** argv) {
    BaseEngine::ApplicationSpecification spec;
    spec.name = "Raytracer";

    BaseEngine::Application* app = new BaseEngine::Application(spec);
    app->pushLayer<ApplicationLayer>();
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
