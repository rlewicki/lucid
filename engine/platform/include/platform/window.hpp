#pragma once

#include "devices/gpu/gpu.hpp"

namespace lucid::platform
{
    struct FWindowDefiniton
    {
        char const* title;
        u16 X, Y;
        u16 Width, Height;
        bool sRGBFramebuffer;
        bool bHidden;
    };

    class CWindow
    {
      public:
        CWindow() = default;

        virtual void Init() = 0;
        
        virtual void Prepare() = 0;
        virtual void Swap() = 0;
        virtual void Clear() = 0;

        virtual glm::vec2 GetPosition() const = 0;

        virtual u16 GetWidth() const = 0;
        virtual u16 GetHeight() const = 0;
        
        virtual float GetAspectRatio() const = 0;

        virtual gpu::CFramebuffer* GetFramebuffer() const = 0;
        
        virtual void Show() = 0;
        virtual void Hide() = 0;

        virtual void Destroy() = 0;

        inline bool IsRequestedClose() const {return bRequestedClose ;}
        
        // Events callbacks
        
        virtual void OnFocusGained() = 0;
        virtual void OnResize(const u16& InWidth, const u16& InHeight) = 0;
        virtual void OnRequestClose() { bRequestedClose = true; }

        gpu::FGPUState* GetGPUState() { return &GPUStateForMyContext; }
        
        virtual ~CWindow() = default;

        // Development stuff

#if DEVELOPMENT
        // Dear ImgUi
        virtual void ImgUiSetup() = 0;
        virtual void ImgUiStartNewFrame() = 0;
        virtual void ImgUiDrawFrame() = 0;
#endif

    protected:
        bool bRequestedClose = false;
        gpu::FGPUState GPUStateForMyContext;
    };

    CWindow* CreateNewWindow(const FWindowDefiniton& Definiton);

} // namespace lucid::platform