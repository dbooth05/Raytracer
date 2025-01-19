#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

void initSDL(SDL_Window*& wind, SDL_GLContext& context) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set SDL to use OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    wind = SDL_CreateWindow(
        "Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!wind) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    context = SDL_GL_CreateContext(wind);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Enable vsync
    SDL_GL_SetSwapInterval(1);

    std::cout << "OpenGL initialized. Version: " << glGetString(GL_VERSION) << std::endl;

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForOpenGL(wind, context);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void cleanup(SDL_Window*& wind, SDL_GLContext& context) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (context) SDL_GL_DeleteContext(context);
    if (wind) SDL_DestroyWindow(wind);
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    SDL_Window* wind = nullptr;
    SDL_GLContext context;

    initSDL(wind, context);
    
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            renderGUI();

        }

        // Clear screen
        ImGui::Render();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // background color
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        SDL_GL_SwapWindow(wind);
    }

    cleanup(wind, context);

    return 0;
}