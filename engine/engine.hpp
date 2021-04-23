﻿#pragma once

#include "common/types.hpp"
#include "devices/gpu/shaders_manager.hpp"
#include "resources/resources_holder.hpp"
#include "resources/texture_resource.hpp"
#include "resources/mesh_resource.hpp"

namespace lucid
{
    using TexturesHolder = resources::CResourcesHolder<resources::CTextureResource>;
    using MeshesHolder = resources::CResourcesHolder<resources::CMeshResource>;
    
    enum class EEngineInitError : u8
    {
        NONE,
        GPU_INIT_ERROR,
    };

    struct FEngineConfig
    {
        bool bHotReloadShaders;
    };
    
    class CEngine
    {
        
    public:

        EEngineInitError InitEngine(const FEngineConfig& InEngineConfig);
        void             LoadResources();
        
        inline FResourceDatabase&   GetResourceDatabase()   { return ResourceDatabase; }
        inline TexturesHolder&      GetTexturesHolder() { return TexturesHolder; } 
        inline MeshesHolder&        GetMeshesHolder()   { return MeshesHolder; }

        inline gpu::CShadersManager& GetShadersManager() { return ShadersManager; }

    protected:

        gpu::CShadersManager ShadersManager;

        FResourceDatabase ResourceDatabase;

        MeshesHolder    MeshesHolder;
        TexturesHolder  TexturesHolder;

    };

    extern CEngine GEngine;
}