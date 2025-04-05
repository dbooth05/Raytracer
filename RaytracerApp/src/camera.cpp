#include "camera.hpp"

void Camera::onResize(uint32_t wd, uint32_t ht) {

    if (f_img) {
        if (f_img->getWd() == wd && f_img->getHt())
            return;
        f_img->resize(wd, ht);
    } else {
        f_img = std::make_shared<BaseEngine::Image>(wd, ht, BaseEngine::ImageFormat::RGBA);
    }

    delete[] img_data;
    img_data = new uint32_t[wd * ht];
}

void Camera::render() {

    for (uint32_t y = 0; y < f_img->getHt(); y++) {
        for (uint32_t x = 0; x < f_img->getWd(); x++) {
            glm::vec2 coord = {
                (float) x / (float) f_img->getWd(),
                (float) y / (float) f_img->getHt()
            };

            coord = coord * 2.0f - 1.0f; // -1 -> 1

            img_data[x + y * f_img->getWd()] = perPixel(coord);
        }
    }

    f_img->setData(img_data);
}

uint32_t Camera::perPixel(glm::vec2 coord) {
    glm::vec3 rayOrig(0.0f, 0.0f, 2.0f);
    glm::vec3 rayDir(coord.x, coord.y, -1.0f);
    float radius = 0.5f;

    // a = ray orig, b = ray dir, c = radius, t = hit dist
    float a = glm::dot(rayDir, rayDir);
    float b = 2.0f * glm::dot(rayOrig, rayDir);
    float c = glm::dot(rayOrig, rayOrig) - radius * radius;

    float discrim = b * b - 4 * a * c;

    if (discrim >= 0.0f) {
        return 0xffff00ff;
    }

    return 0xff000000;
}
