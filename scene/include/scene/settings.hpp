﻿#pragma once
#include <glm/vec2.hpp>

namespace lucid::scene
{
    struct LightSettings
    {
        // Projection matrix
        float Left, Right;
        float Bottom, Top;
        float Near, Far;
    };

}
