#include "renderer.hpp"

static uint32_t Utils::convertToRGBA(const glm::vec4& col) {
        uint8_t r = (uint8_t)(col.r * 255.0f);
        uint8_t g = (uint8_t)(col.g * 255.0f);
        uint8_t b = (uint8_t)(col.b * 255.0f);
        uint8_t a = (uint8_t)(col.a * 255.0f);

        return (a << 24) | (b << 16) | (g << 8) | r;
}

void Renderer::onResize(uint32_t wd, uint32_t ht) {

    if (f_img) {
        // no resize
        if (f_img->getWd() == wd && f_img->getHt() == ht) return;

        f_img->resize(wd, ht);
    } else {
        f_img = std::make_shared<BaseEngine::Image>(wd, ht, BaseEngine::ImageFormat::RGBA);
    }

    delete[] img_data;
    img_data = new uint32_t[wd * ht];
}

void Renderer::render(const Camera& cam) {

    const glm::vec3& orig = cam.getPos();

    Ray ray;
    ray.orig = cam.getPos();

    for (uint32_t y = 0; y < f_img->getHt(); y++) {
        for (uint32_t x = 0; x < f_img->getWd(); x++) {
            ray.dir = cam.getRayDirs()[x + y * f_img->getWd()];

            glm::vec4 col = traceRay(ray);
            col = glm::clamp(col, glm::vec4(0.0f), glm::vec4(1.0f));
            img_data[x + y * f_img->getWd()] = Utils::convertToRGBA(col);
        }
    }

    f_img->setData(img_data);
}

glm::vec4 Renderer::traceRay(Ray ray) {
    float radius = 0.5f;

    // a = ray orig, b = ray dir, c = radius, t = hit dist
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0f * glm::dot(ray.orig, ray.dir);
    float c = glm::dot(ray.orig, ray.orig) - radius * radius;

    float discrim = b * b - 4.0f * a * c;

    if (discrim < 0.0f) {
        return glm::vec4(0, 0, 0, 1);
    }

    float closest = (-b - glm::sqrt(discrim)) / (2.0f * a);
    float t0 = (-b + glm::sqrt(discrim)) / (2.0f * a); // second hit dist

    glm::vec3 hitPnt = ray.orig + ray.dir * closest;
    glm::vec3 norm = glm::normalize(hitPnt);

    glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));
    float ligthIntens = glm::max(glm::dot(norm, -lightDir), 0.0f); // cos(angle)

    glm::vec3 sphereCol(1, 0, 1);
    sphereCol *= ligthIntens;

    return glm::vec4(sphereCol, 1.0f);
}
