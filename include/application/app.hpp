#ifndef APP_HPP
#define APP_HPP

#include "constants.hpp"

class App {
    public:        
        App(int wd, int ht) : width(wd), height(ht) {
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
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
            );

            if (!wind) {
                std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
                exit(EXIT_FAILURE);
            }

            cont = SDL_GL_CreateContext(wind);
            if (!cont) {
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
            ImGui_ImplSDL2_InitForOpenGL(wind, cont);
            ImGui_ImplOpenGL3_Init("#version 130");
        }

        ~App() {
            if (ImGui::GetCurrentContext()) {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplSDL2_Shutdown();
                ImGui::DestroyContext();
            }
            if (cont) SDL_GL_DeleteContext(cont);
            if (wind) SDL_DestroyWindow(wind);
            SDL_Quit();
        }
    
        void run() {
            bool running = true;
            SDL_Event e;

            while (running) {
                while (SDL_PollEvent(&e)) {
                    ImGui_ImplSDL2_ProcessEvent(&e);
                    if (e.type == SDL_QUIT) {
                        running = false;
                    }
                }

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();

                // stuff to render goes here
                {
                    camera.cameraSettings();

                    ImGui::ShowDemoWindow();
                }

                ImGui::Render();

                // Setting background color
                glClearColor(camera.bg[R], camera.bg[G], camera.bg[B], camera.bg[A]); // background color

                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                
                // Swap buffers
                SDL_GL_SwapWindow(wind);
            }
        }

    private:


    private:
        SDL_Window* wind = nullptr;
        SDL_GLContext cont;

    private:
        int width;
        int height;

    private:
        Camera camera;
};

#endif