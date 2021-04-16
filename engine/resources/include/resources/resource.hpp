﻿#pragma once

#include "common/strings.hpp"

namespace lucid::resources
{
    #define RESOURCE_NAME_LENGTH_SIZE (sizeof(u32))
    #define RESOURCE_DATA_SIZE_SIZE (sizeof(u64))
    #define RESOURCE_SERIALIZATION_VERSION_SIZE (sizeof(u32))
    #define RESOURCE_FILE_HEADER_SIZE (sizeof(lucid::UUID) + sizeof(EResourceType) + RESOURCE_SERIALIZATION_VERSION_SIZE + RESOURCE_DATA_SIZE_SIZE + RESOURCE_NAME_LENGTH_SIZE)

    enum EResourceType : u8
    {
        TEXTURE,
        MESH
    };
    
    /** Base class that represents a resource whose data can be stored in main/video memory or both */
    class CResource
    {
    public:

        CResource(const UUID& InID, const FString& InName, const FString& InFilePath, const u64& InOffset, const u64& InDataSize, const u32& InAssetSerializationVersion);

        virtual EResourceType GetType() const = 0;

        /**
         * Called by LoadResource so the child class gets chance to load it's metadata,
         * e.x. the texture will read it's width and height in this method.
         */
        virtual void LoadMetadata(FILE* ResourceFile) = 0; 

        virtual void LoadDataToMainMemorySynchronously() = 0;

        /**
         * Implementations are free to memory map the file if the data is not already loaded to the main memory
         * or just is the data loaded by the previous call to LoadDataToMainMemory*
         */
        virtual void LoadDataToVideoMemorySynchronously() = 0;

        virtual void SaveSynchronously(FILE* ResourceFile) = 0;
        
        virtual void FreeMainMemory() = 0;
        virtual void FreeVideoMemory() = 0;

        virtual ~CResource() = default;

    protected:

        void SaveHeader(FILE* ResourceFile);
        
        const UUID              ID;
        FString                 Name;

        /** Path the the file from which this resource was loaded */
        const FString       FilePath;

        /** Offset at which the resource is stored in the file */
        u64                 Offset;
        
        /** Size of the resource data in bytes, e.x. image data excluding the metadata like UUID, type etc */
        u64                 DataSize; 

        u32                 AssetSerializationVersion = -1;
       
        bool                IsVideoMemoryFreed = false;
        bool                IsMainMemoryFreed = false;
    };

    template <typename R, typename = std::enable_if<std::is_base_of<CResource, R>::value>>
    R* LoadResource(FILE* ResourceFile, const FString& ResourceFilePath);
}

#include "resources/resource.tpp"