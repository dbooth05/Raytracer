#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Add vector addition
    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    // Add scalar to vector
    vec3 operator+(float val) const {
        return vec3(x + val, y + val, z + val);
    }

    // Subtract vectors
    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product
    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    vec3 cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Normalize vector
    vec3 normalize() const {
        float len = std::sqrt(x * x + y * y + z * z);
        return (*this) * (1.0f / len);
    }
};

#endif // vec3_HPP
