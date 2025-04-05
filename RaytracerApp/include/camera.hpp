#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "image.hpp" // from BaseEngine
#include <memory>
#include <glm/glm.hpp>

class Camera {
    public:
        Camera() = default;

        void onResize(uint32_t wd, uint32_t ht);
        void render();

        std::shared_ptr<BaseEngine::Image> getFinalImg() const {
            return f_img;
        }

    private:
        uint32_t perPixel(glm::vec2);

    private:
        std::shared_ptr<BaseEngine::Image> f_img; // final img
        uint32_t* img_data = nullptr;
};

#endif
