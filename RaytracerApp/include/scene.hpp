#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "shapes.hpp"
#include "material.hpp"

struct Scene {
    std::vector<Sphere> Spheres;
    std::vector<Material> Materials;

    glm::vec3 background{0.6f, 0.7f, 0.9f};
    int bounces = 5;
};

#endif
