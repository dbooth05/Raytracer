#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "shapes.hpp"

struct Scene {
    std::vector<Sphere> Spheres;
    glm::vec3 background{0.0f, 0.0f, 0.0f};
    int bounces = 10;
};

#endif
