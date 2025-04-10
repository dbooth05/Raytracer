#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>

struct Material {
    glm::vec3 albedo { 1.0f };
    float roughness = 1.0;
    float metallic = 0.0f;
};

#endif
