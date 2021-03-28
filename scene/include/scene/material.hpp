#pragma once

namespace lucid::gpu
{
    class CShader;
    class CTexture;
} // namespace lucid::gpu

namespace lucid::scene
{
    class CMaterial
    {
      public:
        explicit CMaterial(gpu::CShader* InCustomShader = nullptr) : CustomShader(InCustomShader) {}

        /*
         * Function responsible for sending material's properties to the shader as uniform variables
         * It's called by the Renderer, the renderer is free to decide which shader will be actually used
         * it can use the Material's 'CustomShader' or provide some other shader as it sees fit
         */
        virtual void SetupShader(gpu::CShader* Shader) = 0;

        inline void SetCustomShader(gpu::CShader* Shader) { CustomShader = Shader; }
        inline gpu::CShader* GetCustomShader() const { return CustomShader; }

        virtual ~CMaterial() = default;

      protected:

        gpu::CShader* CustomShader;
    };
} // namespace lucid::scene
