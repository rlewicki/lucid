#pragma once

#include <cstdint>
#include "SDL2/SDL_keycode.h"

namespace lucid
{
    enum MouseButton : uint8_t
    {
        LEFT = 1,
        MIDDLE = 2,
        RIGHT = 4
    };

    struct MousePosition
    {
        float X, Y;
        float DeltaX, DeltaY;
    };

    void ReadEvents();

    bool IsKeyPressed(const SDL_Keycode& KeyCode);
    bool WasKeyPressed(const SDL_Keycode& KeyCode);
    bool WasKeyReleased(const SDL_Keycode& KeyCode);

    bool IsMouseButtonPressed(const MouseButton& Button);
    bool WasMouseButtonPressed(const MouseButton& Button);
    bool WasMouseButtonReleased(const MouseButton& Button);

    MousePosition GetMousePostion();
    float GetMouseWheelDelta();
} // namespace lucid