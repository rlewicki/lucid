#pragma once

#include "scene/actors/lights.hpp"
#include "settings.hpp"
#include "devices/gpu/texture.hpp"
#include "devices/gpu/viewport.hpp"
#include "platform/input.hpp"
#include "scene/render_scene.hpp"

namespace lucid::gpu
{
    class CFramebuffer;
    class CShader;
    class CTexture;
}; // namespace lucid::gpu

namespace lucid::scene
{
    class CCamera;

    struct FRenderView
    {
        CCamera*       Camera;
        gpu::FViewport Viewport;
    };

    /////////////////////////////////////
    //         RendererObjects         //
    /////////////////////////////////////

    using RID = u32;

    class CRendererObject
    {
      public:
        explicit CRendererObject(const RID& InId) : Id(InId) {}

        inline RID GetId() const { return Id; }

        virtual void Free() = 0;

        virtual ~CRendererObject() = default;

      protected:
        RID Id;
    };

    /////////////////////////////////////
    //           ShadowMaps            //
    /////////////////////////////////////
    class CShadowMap : public CRendererObject
    {
      public:
        CShadowMap(const RID& InId, gpu::CTexture* InShadowMapTexture, const u8& InShadowMapQuality)
        : CRendererObject(InId), ShadowMapTexture(InShadowMapTexture), ShadowMapQuality(InShadowMapQuality)
        {
        }

        inline gpu::CTexture* GetShadowMapTexture() const { return ShadowMapTexture; }
        inline u8             GetQuality() const { return ShadowMapQuality; }

        virtual void Free() override;

      private:
        u8             ShadowMapQuality;
        gpu::CTexture* ShadowMapTexture;
    };

#if DEVELOPMENT
    /** Stores ids of the objects on the scene, used for picking in tools */
    struct FHitMap
    {
        inline u64 GetIdAtMousePositon(const glm::vec2& MousePosition) const
        {
            if (MousePosition.x > 0 && (int)MousePosition.x < Width && MousePosition.y > 0 && (int)MousePosition.y < Height)
            {
                return CachedTextureData[(Width * (Height - (int)MousePosition.y)) + (int)MousePosition.x];
            }
            return 0;
        }

        u32* CachedTextureData;
        u32  Width, Height;
    };

    /** Stores information about the last rendered frame, populated by the renderer in Render() */
    struct FRenderStats
    {
        float FrameTimeMiliseconds;
        u32   NumDrawCalls;
        u64   FrameNumber = 0;
    };

    extern FRenderStats GRenderStats;

#endif

    /////////////////////////////////////
    //            Renderer             //
    /////////////////////////////////////
    class CRenderer
    {
      public:
        /////////////////////////////////////
        //        Renderer interface       //
        /////////////////////////////////////

        /**
         * Called before the first Render() call so that the renderer can set itself up, like create additional framebuffers and
         * etc. Can be called multiple time, subsequent Setup() calls have be preceded by Cleanup() calls
         */
        virtual void Setup() = 0;

        /**
         * Renders the scene from the specified view
         */
        virtual void Render(FRenderScene* InSceneToRender, const FRenderView* InRenderView) = 0;

        /**
         * Called before the renderer is deleted so it can cleanup whatever it did in Setup() or during Render(s)().
         */
        virtual void Cleanup() = 0;

        /**
         * Returns the framebuffer which holds the result of last Render() call.
         */
        virtual gpu::CFramebuffer* GetResultFramebuffer() = 0;

        /** Stalls the CPU until GPU finished executing all commands of the previous Render() call.  */
        void WaitForFrameEnd() const { gpu::Finish(); }

        /////////////////////////////////////
        //         Lights/ShadowMaps       //
        /////////////////////////////////////

        CDirectionalLight* CreateDirectionalLight(const FDString& InName, IActor* InParent, CWorld* InWorld, const bool& CastsShadow);
        CSpotLight*        CreateSpotLight(const FDString& InName, IActor* InParent, CWorld* InWorld, const bool& CastsShadow);
        CPointLight*       CreatePointLight(const FDString& InName, IActor* InParent, CWorld* InWorld, const bool& CastsShadow);

        CShadowMap* CreateShadowMap(const ELightType& InLightType);
        void        RemoveShadowMap(CShadowMap* InShadowMap);

#if DEVELOPMENT
        inline const FHitMap& GetCachedHitMap() const { return CachedHitMap; }
        inline gpu::CTexture* GetLightBulbTexture() const { return LightBulbTexture; }
#endif

        virtual ~CRenderer() = default;

        glm::uvec2 ResultResolution;

      protected:
        /** Lights and shadow maps arrays */
        CLight**     CreatedLights     = nullptr;
        CShadowMap** CreatedShadowMaps = nullptr;

        /** Default quality used when creating  shadow maps - 0 lowest */
        u8 DefaultShadowMapQuality = 1;
        u8 DefaultLightQuality     = 1;

        /** Size of a shadow map for a given quality  */
        const glm::ivec2 ShadowMapSizeByQuality[3] = {
            { 512, 512 },
            { 1024, 1024 },
            { 2048, 2048 },
        };

        const LightSettings LightSettingsByQuality[3] = { { -10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.f },
                                                          { -10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 35.f },
                                                          { -10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 70.f } };

#if DEVELOPMENT
        /** Used to visualize light sources in the editor */
        gpu::CTexture* LightBulbTexture;

        FHitMap CachedHitMap;
#endif
    };
} // namespace lucid::scene
