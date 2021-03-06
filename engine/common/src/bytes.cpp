#include "common/bytes.hpp"

namespace lucid
{
    FBinaryData EMPTY_BINARY_DATA;

    void* CopyBytes(const char* InToCopy, const u64& InCount, const u64& BufferSize)
    {
        assert(InToCopy);

        void* Copied = malloc(BufferSize == 0 ? InCount : BufferSize);
        memcpy(Copied, InToCopy, InCount);
        return Copied;        
    }

    FMemBuffer CreateMemBuffer(const u32& BufferCapacity)
    {
        char* p = (char*)malloc(BufferCapacity);
        Zero(p, BufferCapacity);
        return FMemBuffer{ p, BufferCapacity };
    }
} // namespace lucid
