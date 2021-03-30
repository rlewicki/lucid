#pragma once

#include "devices/gpu/gpu.hpp"

namespace lucid::platform
{
    struct FWindowDefiniton
    {
        char const* title;
        u16 x, y;
        u16 width, height;
        bool sRGBFramebuffer;
    };

    class CWindow
    {
      public:
        CWindow() = default;

        virtual void Init() = 0;
        
        virtual void Swap() = 0;
        virtual void Prepare() = 0;

        virtual u16 GetWidth() const = 0;
        virtual u16 GetHeight() const = 0;
        virtual float GetAspectRatio() const = 0;
        virtual gpu::CFramebuffer* GetFramebuffer() const = 0;
        
        virtual void Show() = 0;
        virtual void Hide() = 0;

        virtual void Destroy() = 0;

        // Events callbacks
        
        virtual void OnFocusGained() = 0;

        gpu::FGPUState* GetGPUState() { return &GPUStateForMyContext; };
        
        virtual ~CWindow() = default;

        // Development stuff

#if DEVELOPMENT
        // Dear ImgUi
        virtual void ImgUiSetup() = 0;
        virtual void ImgUiStartNewFrame() = 0;
        virtual void ImgUiDrawFrame() = 0;
#endif

    protected:
        gpu::FGPUState GPUStateForMyContext;
    };

    CWindow* CreateWindow(const FWindowDefiniton& Definiton);

} // namespace lucid::platform