#pragma once

#include "settings.hpp"
#include "common/types.hpp"
#include "glm/glm.hpp"

namespace lucid::gpu
{
    class CShader;
    class CTexture;
    class CFramebuffer;
    class CCubemap;
} // namespace lucid::gpu

namespace lucid::scene
{
    class CShadowMap;

    enum class ELightType : u8
    {
        DIRECTIONAL = 1,
        POINT,
        SPOT
    };

    class CLight
    {
      public:
        CLight() = default;

        virtual ELightType GetType() const = 0;
        virtual ~CLight() = default;

        /** Recalculates the light space matrix when e.x. the light moves or is initially created */
        virtual void UpdateLightSpaceMatrix(const LightSettings& LightSettings) = 0;

        /** Sets up the shader's uniform to use this light's data */
        virtual void SetupShader(gpu::CShader* InShader) const;
        virtual void SetupShadowMapShader(gpu::CShader* InShader) = 0;

        glm::vec3   Position        { 0, 0, 0 };
        glm::vec3   Color           { 0, 0, 0 };
        u8          Quality         = 1;

        CShadowMap* ShadowMap       = nullptr;
    };

    /////////////////////////////////////
    //        Directional light        //
    /////////////////////////////////////

    class CDirectionalLight : public CLight
    {
      public:
        CDirectionalLight() = default;

        virtual void UpdateLightSpaceMatrix(const LightSettings& LightSettings) override;
        virtual void SetupShader(gpu::CShader* InShader) const override;
        virtual void SetupShadowMapShader(gpu::CShader* InShader) override;

        virtual ELightType GetType() const override { return ELightType::DIRECTIONAL; }

        glm::vec3 Direction = { 0, 0, 0 };
        glm::vec3 LightUp{ 0, 1, 0 };
        glm::mat4 LightSpaceMatrix{ 1 };

        CShadowMap* ShadowMap = nullptr;
    };

    /////////////////////////////////////
    //            Spot light           //
    /////////////////////////////////////

    class CSpotLight : public CLight
    {
    public:
        virtual ELightType GetType() const override { return ELightType::SPOT; }

        virtual void UpdateLightSpaceMatrix(const LightSettings& LightSettings) override;
        virtual void SetupShader(gpu::CShader* InShader) const override;
        virtual void SetupShadowMapShader(gpu::CShader* InShader) override;

        glm::vec3 Direction { 0, 0, 0 };
        glm::vec3 LightUp   { 0, 1, 0 };

        glm::mat4 LightSpaceMatrix { 1 };

        float Constant       = 0;
        float Linear         = 0;
        float Quadratic      = 0;
        float InnerCutOffRad = 0;
        float OuterCutOffRad = 0;
    };

    /////////////////////////////////////
    //           Point light           //
    /////////////////////////////////////

    class CPointLight : public CLight
    {
      public:
        virtual ELightType GetType() const override { return ELightType::POINT; }

        virtual void UpdateLightSpaceMatrix(const LightSettings& LightSettings) override;
        virtual void SetupShader(gpu::CShader* InShader) const override;
        virtual void SetupShadowMapShader(gpu::CShader* InShader) override;

        float Constant  = 0;
        float Linear    = 0;
        float Quadratic = 0;

        glm::mat4 LightSpaceMatrices[6];

        float NearPlane = 1.f;
        float FarPlane  = 25.f;
    };
} // namespace lucid::scene