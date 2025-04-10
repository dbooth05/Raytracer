#include "renderer.hpp"
#include "random.hpp"

#include <iostream>

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

    active_scene = &scene;
    active_camera = &cam;

    for (uint32_t y = 0; y < f_img->getHt(); y++) {
        for (uint32_t x = 0; x < f_img->getWd(); x++) {
            glm::vec4 col = perPixel(x, y);
            col = glm::clamp(col, glm::vec4(0.0f), glm::vec4(1.0f));
            img_data[x + y * f_img->getWd()] = Utils::convertToRGBA(col);
        }
    }

    f_img->setData(img_data);
}

Renderer::HitPayload Renderer::traceRay(const Ray& ray) {


    int closestSp = -1;
    float hitDist = std::numeric_limits<float>::max();

    for (size_t i = 0; i < active_scene->Spheres.size(); i++) {

        const Sphere& sp = active_scene->Spheres[i];
        glm::vec3 orig = ray.orig - sp.pos;

        float a = glm::dot(ray.dir, ray.dir);
        float b = 2.0f * glm::dot(orig, ray.dir);
        float c = glm::dot(orig, orig) - sp.radius * sp.radius;

        float discrim = b * b - 4.0f * a * c;
        if (discrim < 0.0f) continue;

        float closest = (-b - glm::sqrt(discrim)) / (2.0f * a);
        if (closest > 0.0f && closest < hitDist) {
            hitDist = closest;
            closestSp = (int) i;
        }
    }

    if (closestSp < 0) return miss(ray);

    return closestHit(ray, hitDist, closestSp);
}

Renderer::HitPayload Renderer::closestHit(const Ray& ray, float hit_dist, int obj_idx) {

    Renderer::HitPayload payload;
    payload.hit_dist = hit_dist;
    payload.obj_idx = obj_idx;

    const Sphere& closestSp = active_scene->Spheres[obj_idx];

    glm::vec3 orig = ray.orig - closestSp.pos;
    payload.world_pos = orig + ray.dir * hit_dist;
    payload.world_norm = glm::normalize(payload.world_pos);

    payload.world_pos += closestSp.pos;

    return payload;
}

Renderer::HitPayload Renderer::miss(const Ray& ray) {
    Renderer::HitPayload payload;
    payload.hit_dist = -1.0f;
    return payload;
}

glm::vec4 Renderer::perPixel(uint32_t x, uint32_t y) {
    Ray ray;
    ray.orig = active_camera->getPos();
    ray.dir = active_camera->getRayDirs()[x + y * f_img->getWd()];

    glm::vec3 col(0.0f);
    float multiplier = 1.0f;

    for (int i = 0; i < active_scene->bounces; i++) {
        Renderer::HitPayload payload = traceRay(ray);
        if (payload.hit_dist < 0.0f) {
            glm::vec3 sky = active_scene->background;
            col += sky * multiplier;
            break;
        }

        glm::vec3 light_dir = glm::normalize(glm::vec3(-1, -1, -1));
        float light_intens = glm::max(glm::dot(payload.world_norm, -light_dir), 0.0f); // == cos(angle)

        const Sphere& sp = active_scene->Spheres[payload.obj_idx];
        // glm::vec3 spCo = sp.albedo;
        // spCol *= light_intens;
        // col += spCol * multiplier;
        //
        // multiplier *= 0.7f;
        //
        // ray.orig = payload.world_pos + payload.world_norm * 0.001f;
        // ray.dir = glm::reflect(ray.dir, payload.world_norm);

        const Material& m = active_scene->Materials[sp.mat_idx];
        glm::vec3 spCol = m.albedo;
        spCol *= light_intens;
        col += spCol * multiplier;

        multiplier *= 0.5f;

        ray.orig = payload.world_pos + payload.world_norm + 0.0001f;
        ray.dir = glm::reflect(ray.dir, payload.world_norm + m.roughness * BaseEngine::Random::Vec3(-0.5f, 0.5f));
    }

    return glm::vec4(col, 1.0f);
}
