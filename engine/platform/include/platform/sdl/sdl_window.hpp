#pragma once

#include "devices/gpu/framebuffer.hpp"
#include "devices/gpu/gpu.hpp"
#include "platform/window.hpp"

#if DEVELOPMENT
#include "imgui.h"
#endif

struct SDL_Window;
typedef void* SDL_GLContext;

namespace lucid::platform
{
    class SDLWindow : public CWindow
    {
      public:
        SDLWindow(SDL_Window* InSDLWindow, SDL_GLContext InContext, const u16& InWidth, const u16& InHeight);

        virtual void Init() override;

        virtual void Prepare() override;
        virtual void Swap() override;
        virtual void Clear() override;

        virtual glm::vec2 GetPosition() const override;
        
        virtual u16 GetWidth() const override;
        virtual u16 GetHeight() const override;
        
        virtual float GetAspectRatio() const override;

        virtual gpu::CFramebuffer* GetFramebuffer() const override;

        virtual void Show() override;
        virtual void Hide() override;

        virtual void OnFocusGained() override;
        virtual void OnResize(const u16& InWidth, const u16& InHeight) override;


#if DEVELOPMENT
        
        virtual void ImgUiSetup() override;        
        virtual void ImgUiStartNewFrame() override;
        virtual void ImgUiDrawFrame() override;

#endif

        
        virtual void Destroy() override;

        virtual ~SDLWindow() = default;

    private:

        float AspectRatio;
        u32 Width, Height;
        SDL_Window* MySDLWindow;
        SDL_GLContext MyGLContext;
        gpu::CFramebuffer* WindowFramebuffer;
    };
}; // namespace lucid::platform