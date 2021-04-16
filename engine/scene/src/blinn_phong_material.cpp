#include "scene/blinn_phong_material.hpp"

#include "devices/gpu/shader.hpp"

#include "common/log.hpp"

#include "resources/mesh_resource.hpp"
#include "resources/texture_resource.hpp"

namespace lucid::scene
{
    static const FSString SHININESS("uMaterialShininess");
    static const FSString DIFFUSE_COLOR("uMaterialDiffuseColor");
    static const FSString SPECULAR_COLOR("uMaterialSpecularColor");

    CBlinnPhongMaterial::CBlinnPhongMaterial(gpu::CShader* InShader) : CMaterial(InShader) {}

    void CBlinnPhongMaterial::SetupShader(gpu::CShader* Shader)
    {
        Shader->SetInt(SHININESS, Shininess);
        Shader->SetVector(DIFFUSE_COLOR, DiffuseColor);
        Shader->SetVector(DIFFUSE_COLOR, SpecularColor);
    };

    /* ---------------------------------------------------------------------------*/

    static const FSString DIFFUSE_MAP("uMaterialDiffuseMap");
    static const FSString SPECULAR_MAP("uMaterialSpecularMap");
    static const FSString NORMAL_MAP("uMaterialNormalMap");
    static const FSString HAS_SPECULAR_MAP("uMaterialHasSpecularMap");
    static const FSString HAS_NORMAL_MAP("uMaterialHasNormalMap");
    static const FSString HAS_DISPLACEMENT_MAP("uMaterialHasDisplacementMap");
    static const FSString DISPLACEMENT_MAP("uMaterialDisplacementMap");

    CBlinnPhongMapsMaterial::CBlinnPhongMapsMaterial(gpu::CShader* InShader) : CMaterial(InShader) {}

    void CBlinnPhongMapsMaterial::SetupShader(gpu::CShader* Shader)
    {
        Shader->SetInt(SHININESS, Shininess);
        Shader->UseTexture(DIFFUSE_MAP, DiffuseMap);

        if (SpecularMap != nullptr)
        {
            Shader->UseTexture(SPECULAR_MAP, SpecularMap);
            Shader->SetBool(HAS_SPECULAR_MAP, true);
        }
        else
        {
            Shader->SetBool(HAS_SPECULAR_MAP, false);
            Shader->SetVector(SPECULAR_COLOR, SpecularColor);
        }

        if (NormalMap != nullptr)
        {
            Shader->UseTexture(NORMAL_MAP, NormalMap);
            Shader->SetBool(HAS_NORMAL_MAP, true);
        }
        else
        {
            Shader->SetBool(HAS_NORMAL_MAP, false);
        }

        if (DisplacementMap != nullptr)
        {
            Shader->UseTexture(DISPLACEMENT_MAP, DisplacementMap);
            Shader->SetBool(HAS_DISPLACEMENT_MAP, true);
        }
        else
        {
            Shader->SetBool(HAS_DISPLACEMENT_MAP, false);
        }
    };

    CMaterial* CreateBlinnPhongMapsMaterial(const FString& InMeshName, resources::CMeshResource* InMesh, gpu::CShader* InShader)
    {
        // gpu::CTexture* FallbackTexture = resources::TexturesHolder.GetDefaultResource()->TextureHandle;
        //
        // CBlinnPhongMapsMaterial* Material = new CBlinnPhongMapsMaterial(InShader);
        // Material->Shininess = 32;
        //
        // if (InMesh->DiffuseMap == nullptr)
        // {
        //     LUCID_LOG(ELogLevel::INFO, "Mesh is missing a diffuse map");
        //     Material->DiffuseMap = FallbackTexture;
        // }
        // else
        // {
        //     Material->DiffuseMap = InMesh->DiffuseMap->TextureHandle;
        // }
        //
        // if (InMesh->SpecularMap == nullptr)
        // {
        //     LUCID_LOG(ELogLevel::INFO, "Mesh is missing a specular map");
        //     Material->SpecularMap = FallbackTexture;
        // }
        // else
        // {
        //     Material->SpecularMap = InMesh->SpecularMap->TextureHandle;
        // }
        //
        // if (InMesh->NormalMap == nullptr)
        // {
        //     LUCID_LOG(ELogLevel::INFO, "Mesh is missing a normal map");
        //     Material->NormalMap = FallbackTexture;
        // }
        // else
        // {
        //     Material->NormalMap = InMesh->NormalMap->TextureHandle;
        // }
        //
        // return Material;
        return nullptr;
    }
} // namespace lucid::scene