#pragma once

#include "common/strings.hpp"
#include "common/math.hpp"
#include "devices/gpu/buffer.hpp"

namespace lucid::gpu
{
    class Texture;

    struct BufferBinding
    {
        Buffer* BufferToUse = nullptr;
        BufferBindPoint BindPoint = BufferBindPoint::UNBOUND;
        int32_t Index = -1;

        bool IsValid = false;
    };

    class Shader
    {
      public:
        virtual void Use() = 0;
        virtual void Disable() = 0;

        virtual void SetupTextureBindings() = 0;
        virtual void SetupBuffersBindings() = 0;

        virtual void SetInt(const String& UniformName, const uint32_t& Value) = 0;
        virtual void SetFloat(const String& UniformName, const float& Value) = 0;
        virtual void SetBool(const String& UniformName, const bool& Value) = 0;

        virtual void SetVector(const String& UniformName, const math::vec2& Value) = 0;
        virtual void SetVector(const String& UniformName, const math::vec3& Value) = 0;
        virtual void SetVector(const String& UniformName, const math::vec4& Value) = 0;

        virtual void SetVector(const String& UniformName, const math::ivec2& Value) = 0;
        virtual void SetVector(const String& UniformName, const math::ivec3& Value) = 0;
        virtual void SetVector(const String& UniformName, const math::ivec4& Value) = 0;

        virtual void SetMatrix(const String& UniformName, const math::mat4& Value) = 0;

        virtual void UseTexture(const String& TextureName, Texture* TextureToUse) = 0;

        virtual void AddBinding(BufferBinding* Binding) = 0;

        virtual ~Shader() = default;
        // TODO Matrices
    };

    Shader* CompileShaderProgram(const String& VertexShaderSource, const String& FragementShaderSource);
} // namespace lucid::gpu
