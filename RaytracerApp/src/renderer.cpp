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

void Renderer::render(const Scene& scene, const Camera& cam) {

    const glm::vec3& orig = cam.getPos();

    Ray ray;
    ray.orig = cam.getPos();

    for (uint32_t y = 0; y < f_img->getHt(); y++) {
        for (uint32_t x = 0; x < f_img->getWd(); x++) {
            ray.dir = cam.getRayDirs()[x + y * f_img->getWd()];

            glm::vec4 col = traceRay(scene, ray);
            col = glm::clamp(col, glm::vec4(0.0f), glm::vec4(1.0f));
            img_data[x + y * f_img->getWd()] = Utils::convertToRGBA(col);
        }
    }

    f_img->setData(img_data);
}

glm::vec4 Renderer::traceRay(const Scene& scene, Ray ray) {

    if (scene.Spheres.size() == 0) {
        return glm::vec4(0, 0, 0, 1);
    }

    const Sphere* closestSp = nullptr;
    float hitDist = std::numeric_limits<float>::max();

    for (const Sphere& sp : scene.Spheres) {
        glm::vec3 orig = ray.orig - sp.pos;

        float a = glm::dot(ray.dir, ray.dir);
        float b = 2.0f * glm::dot(orig, ray.dir);
        float c = glm::dot(orig, orig) - sp.radius * sp.radius;

        float discrim = b * b - 4.0f * a * c;
        if (discrim < 0.0f) continue;

        float closest = (-b - glm::sqrt(discrim)) / (2.0f * a);
        if (closest < hitDist) {
            hitDist = closest;
            closestSp = &sp;
        }
    }

    if (closestSp == nullptr) return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 orig = ray.orig - closestSp->pos;
    glm::vec3 hitPnt = orig + ray.dir * hitDist;
    glm::vec3 normal = glm::normalize(hitPnt);

    glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));
    float lightIntens = glm::max(glm::dot(normal, -lightDir), 0.0f); // == cos(angle)

    glm::vec3 spCol = closestSp->albedo;
    spCol *= lightIntens;
    return glm::vec4(spCol, 1.0f);
}
