#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "shapes.hpp"
#include "material.hpp"

struct Scene {
    std::vector<Sphere> Spheres;
    std::vector<Material> Materials;

    glm::vec3 background{0.0f, 0.0f, 0.0f};
    int bounces = 5;
};

#endif
