#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <glm/glm.hpp>

class Sphere {
    public:
        glm::vec3 pos{0.0f};
        float radius = 0.5f;

        int mat_idx;
};

#endif
