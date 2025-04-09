#include "application.hpp"
#include "entry.hpp"
#include "image.hpp"

class ExampleLayer : public BaseEngine::Layer {
    public:
        virtual void onUIRender() override {
            ImGui::Begin("Hello");
            ImGui::Button("Button");
            ImGui::End();

            ImGui::ShowDemoWindow();
        }
};

BaseEngine::Application* BaseEngine::createApplicaion(int argc, char** argv) {
    BaseEngine::ApplicationSpecification spec;
    spec.name = "Example";

    BaseEngine::Application* app = new BaseEngine::Application(spec);
    app->pushLayer<ExampleLayer>();
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
