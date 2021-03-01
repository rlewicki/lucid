﻿#include "devices/gpu/shaders_manager.hpp"

#include <stb_ds.h>


#include "common/log.hpp"
#include "devices/gpu/shader.hpp"
#include "platform/fs.hpp"

namespace lucid::gpu
{
    static ShadersManager GShadersManager;

    void ReloadShaders();

    Shader* ShadersManager::CompileShader(const String& ShaderName,
                                          const String& VertexShaderPath,
                                          const String& FragmentShaderPath,
                                          const String& GeometryShaderPath,
                                          const bool& ShouldStoreShader)
    {
        DString VertexShaderSource = platform::ReadFile(VertexShaderPath, true);
        DString FragmentShaderSource = platform::ReadFile(FragmentShaderPath, true);

        DString GeometryShaderSource{""};
        if (GeometryShaderPath.GetLength())
        {
            GeometryShaderSource = platform::ReadFile(GeometryShaderPath, true);
        }

        if (VertexShaderSource.GetLength() == 0)
        {
            LUCID_LOG(LogLevel::WARN, "Failed to read vertex shader source from file %s while compiling shader '%s'",
                      *VertexShaderPath, *ShaderName);
            return nullptr;
        }

        if (FragmentShaderSource.GetLength() == 0)
        {
            LUCID_LOG(LogLevel::WARN, "Failed to read fragment shader source from file %s while compiling shader '%s'",
                      *FragmentShaderPath, *ShaderName);
            VertexShaderSource.Free();
            return nullptr;
        }

        if (GeometryShaderPath.GetLength() > 0 && GeometryShaderSource.GetLength() == 0)
        {
            LUCID_LOG(LogLevel::WARN, "Failed to read geometry shader source from file %s while compiling shader '%s'",
                      *GeometryShaderPath, *ShaderName);
            VertexShaderSource.Free();
            FragmentShaderSource.Free();
            return nullptr;
        }


        Shader* CompiledShader = CompileShader(ShaderName, VertexShaderPath, FragmentShaderPath, GeometryShaderPath);
        if (CompiledShader == nullptr)
        {
            VertexShaderSource.Free();
            FragmentShaderSource.Free();
            GeometryShaderSource.Free();
            return nullptr;
        }

        if (ShouldStoreShader)
        {
            const ShaderInstanceInfo ShaderInstanceInfo{
                CompiledShader, VertexShaderPath, FragmentShaderPath, GeometryShaderPath
            };
            arrput(CompiledShaders, ShaderInstanceInfo);
        }

        return CompiledShader;
    }

    void ShadersManager::EnableHotReload()
    {
        platform::AddDirectoryListener({"shaders/base"}, ReloadShaders);
    }

    void ShadersManager::DisableHotReload()
    {
        platform::RemoveDirectoryListener({"shaders/base"}, ReloadShaders);
    }

    void ReloadShaders()
    {
        for (int i = 0; i < arrlen(GShadersManager.CompiledShaders); ++i)
        {
            const ShaderInstanceInfo& ShaderInfo = GShadersManager.CompiledShaders[i];
            Shader* RecompiledShader = GShadersManager.CompileShader(ShaderInfo.Shader->GetName(), ShaderInfo.VertexShaderPath, ShaderInfo.FragmentShaderPath, ShaderInfo.GeometryShaderPath);
            ShaderInfo.Shader->ReloadShader(RecompiledShader);            
            delete RecompiledShader;
        }
    }
} // namespace lucid::gpu
