#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "image.hpp" // from BaseEngine

#include "scene.hpp"
#include "camera.hpp"
#include "ray.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace Utils {
    static uint32_t convertToRGBA(const glm::vec4& col);
}

class Renderer {
    public:
        Renderer() = default;

        void onResize(uint32_t wd, uint32_t ht);
        void render(const Scene& scene, const Camera& cam);

        std::shared_ptr<BaseEngine::Image> getFinalImg() const {
            return f_img;
        }

    private:
        glm::vec4 traceRay(const Scene& scene, Ray ray);

    private:
        std::shared_ptr<BaseEngine::Image> f_img; // final img
        uint32_t* img_data = nullptr;
};

#endif
