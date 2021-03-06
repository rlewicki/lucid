﻿#pragma once

#include "resources/resource.hpp"
#include "schemas/types.hpp"
#include "scene/actors/actor.hpp"

namespace lucid::gpu
{
    class CCubemap;
    class CTexture;
}; // namespace lucid::gpu

namespace lucid::scene
{
    class CSkybox : public IActor
    {
      public:
        CSkybox(const FDString&              InName,
                IActor*                      InParent,
                CWorld*                      InWorld,
                gpu::CCubemap*               InSkyboxCubemap,
                const u32&                   InWidth,
                const u32&                   InHeight,
                resources::CTextureResource* InFaceTextures[6]);

        virtual float GetVerticalMidPoint() const override;

        static EActorType  GetActorTypeStatic() { return EActorType::SKYBOX; }
        virtual EActorType GetActorType() const override { return EActorType::SKYBOX; }

        virtual void LoadAsset() override;
        virtual void UnloadAsset() override;

        virtual IActor* CreateActorInstance(CWorld* InWorld, const glm::vec3& InSpawnPosition) override;
        virtual IActor* CreateCopy() override { return nullptr; }

        static CSkybox* CreateActor(CSkybox* BaseActorResource, CWorld* InWorld, const FSkyboxDescription& InSkyboxDescription);

        virtual IActor* CreateActorAsset(const FDString& InName) const override;
        static CSkybox* LoadActorAsset(const FSkyboxDescription& InSkyboxDescription);

        virtual void OnAddToWorld(CWorld* InWorld) override;
        virtual void OnRemoveFromWorld(const bool& InbHardRemove) override;
        virtual void CleanupAfterRemove() override;

#if DEVELOPMENT
        /** Editor stuff */
        virtual void UIDrawActorDetails() override;

      protected:
        virtual void InternalSaveToResourceFile(const FString& InFilePath) override;

      public:
#endif
        void FillDescription(FSkyboxDescription& OutDescription) const;

        u32                          Width, Height;
        gpu::CCubemap*               SkyboxCubemap = nullptr;
        resources::CTextureResource* FaceTextures[6]{ nullptr };
        CSkybox const*               BaseSkyboxResource = nullptr;
    };

    CSkybox*
    CreateSkybox(resources::CTextureResource* FaceTextures[6], CWorld* InWorld, const u32& InWidth, const u32& InHeight, const FString& InName);
} // namespace lucid::scene