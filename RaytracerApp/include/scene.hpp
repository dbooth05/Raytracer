#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>

#include "shapes.hpp"

struct Scene {
    std::vector<Sphere> Spheres;
};

#endif
