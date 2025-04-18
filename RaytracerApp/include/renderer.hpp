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
        struct Settings {
            bool accumulate = true;
        };

    public:
        Renderer() = default;

        void onResize(uint32_t wd, uint32_t ht);
        void render(const Scene& scene, const Camera& cam);

        std::shared_ptr<BaseEngine::Image> getFinalImg() const {
            return f_img;
        }

        void resetFrameIdx() { frame_idx = 1; }

        Settings& getSettings() { return settings; }

    private:
        struct HitPayload {
            float hit_dist;
            glm::vec3 world_pos;
            glm::vec3 world_norm;

            int obj_idx;
        };

        glm::vec4 perPixel(uint32_t x, uint32_t y); // ray generation

        HitPayload traceRay(const Ray& ray);
        HitPayload closestHit(const Ray& ray, float hit_dist, int obj_idx);
        HitPayload miss(const Ray& ray);

    private:
        std::shared_ptr<BaseEngine::Image> f_img; // final img
                                                  
        const Scene* active_scene = nullptr;
        const Camera* active_camera = nullptr;
  
        uint32_t* img_data = nullptr;
        glm::vec4* accum_data = nullptr;

        uint32_t frame_idx = 1;

        Settings settings;
};

#endif
