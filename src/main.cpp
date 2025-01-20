#include <iostream>

#include "app.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

void renderGUI() {
    ImGui::Begin("Settings");
        if (ImGui::CollapsingHeader("Options")) {
            static bool option1 = false;
            static int option2 = 50;

            ImGui::Checkbox("Enable 1", &option1);
            ImGui::SliderInt("Adjust Value", &option2, 0, 100);

            if (ImGui::Button("Apply Settings")) {
                std::cout << "Settings applied: Option 1 = " << option1 << ", Option 2 = " << option2 << std::endl;
            }
        }
    ImGui::End();
}

int main(int argc, char* argv[]) {

    App app(SCREEN_WIDTH, SCREEN_HEIGHT);
    app.run();

    app.~App();

    return 0;
}