#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "shapes.hpp"

struct Scene {
    std::vector<Sphere> Spheres;
    glm::vec4 background{0.0f, 0.0f, 0.0f, 1.0f};
};

#endif
