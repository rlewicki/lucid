﻿#pragma once

#include "common/types.hpp"
#include "platform/input.hpp"

namespace lucid::scene
{
    class   CStaticMesh;
    class   CSkybox;
    class   CLight;
    class   CCamera;
    struct  FRenderScene;
    
    /**
     * World represents all of the currently loaded renderable objects and is culled based on camera's position
     * to produce a CRenderScene which is then handed out the Renderer that actually renders the scene.
     * There can be objects dynamically to and unloaded from the world.
     */
    class CWorld
    {
    public:
        void            Init();
        void            AddStaticMesh(CStaticMesh* InStaticMesh);
        void            AddLight(CLight* InLight);
        void            SetSkybox(CSkybox* InSkybox);
        
        FRenderScene*   MakeRenderScene(CCamera* InCamera);
    
    private:
        CStaticMesh**   StaticMeshes = nullptr;
        CLight**        Lights = nullptr;
        CSkybox*        Skybox = nullptr;
    };
}
