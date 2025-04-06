#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <vector>

class Camera {
    public:
        Camera(float vertFov, float near, float far);

        void onUpdate(float ts);
        void onResize(uint32_t wd, uint32_t ht);

        const glm::mat4& getProj() const { return proj; }
        const glm::mat4& getView() const { return view; }
        const glm::mat4& getInvProj() const { return invProj; }
        const glm::mat4& getInvView() const { return invView; }

        const glm::vec3& getPos() const { return pos; }
        const glm::vec3& getDir() const { return forwardDir; }

        const std::vector<glm::vec3>& getRayDirs() const { return rayDirs; }

        float getRotationSpeed();

    private:
        void recalcProj();
        void recalcView();
        void recalcRayDirs();

    private:
        glm::mat4 proj{ 1.0f };
        glm::mat4 view{ 1.0f };
        glm::mat4 invProj { 1.0f };
        glm::mat4 invView { 1.0f };

        float vertFov   = 45.0f;
        float near      = 0.1f;
        float far       = 100.0f;

        glm::vec3 pos {0.0f, 0.0f, 0.0f};
        glm::vec3 forwardDir {0.0f, 0.0f, 0.0f};

        // cached ray dirs
        std::vector<glm::vec3> rayDirs;

        glm::vec2 lastMousePos { 0.0f, 0.0f };

        uint32_t vpWd = 0, vpHt = 0;
};

#endif
