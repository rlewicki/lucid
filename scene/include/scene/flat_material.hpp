#pragma once

#include "scene/material.hpp"
#include "glm/glm.hpp"

namespace lucid::gpu
{
    class Shader;
};

namespace lucid::scene
{
    class FlatMaterial : public Material
    {
      public:
        explicit FlatMaterial(gpu::Shader* CustomShader = nullptr);

        virtual void SetupShader(gpu::Shader* Shader) override;

        // Material properties
        glm::vec3 Color;
    };
}