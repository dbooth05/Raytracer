#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "layer.hpp"

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "imgui.h"
#include "vulkan/vulkan.hpp"

void my_check_vk_result(VkResult err);

struct GLFWwindow;

namespace BaseEngine {
    struct ApplicationSpecification {
        std::string name = "Base Engine";
        uint32_t width = 1600;
        uint32_t height = 900;
    };

    class Application {
        public:
            Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
            ~Application();

            static Application& get();

            void run();
            void setMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

            template<typename T>
            void pushLayer() {
                static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not a subclass of layer!");
                m_LayerStack.emplace_back(std::make_shared<T>())->onAttach();
            }

            void close();

            float getTime();
            GLFWwindow* getWindowHandle() const { return m_WindowHandle; }

            static VkInstance getInstance();
            static VkPhysicalDevice getPhysicalDevice();
            static VkDevice getDevice();

            static VkCommandBuffer getCommandBuffer(bool begin);
            static void FlushCommandBuffer(VkCommandBuffer commandBuffer);

            static void submitResourceFree(std::function<void()>&& func);


        private:
            void init();
            void shutdown();

        private:
            ApplicationSpecification m_Specification;
            GLFWwindow* m_WindowHandle = nullptr;
            bool m_Running = false;

            float m_TimeStep = 0.0f;
            float m_FrameTime = 0.0f;
            float m_LastFrameTime = 0.0f;

            std::vector<std::shared_ptr<Layer>> m_LayerStack;
            std::function<void()> m_MenubarCallback;
    };

    // Implemented by CLIENT
    Application* createApplicaion(int argc, char** argv);
}

#endif
