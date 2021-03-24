#include "misc/basic_shapes.hpp"
#include "devices/gpu/buffer.hpp"
#include "devices/gpu/gpu.hpp"
#include "devices/gpu/vao.hpp"

namespace lucid::misc
{
    gpu::CVertexArray* QuadVertexArray;
    gpu::CVertexArray* CubeVertexArray;

    static const float BASIC_QUAD_VERTEX_DATA[]{
        // pos         //normals //tangents      //tex coords
        -1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f,  0.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f
    };

    float CUBE_VERTICES[] = {
        // positions          // normals //tangents           // texture coords
            -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-right
             1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-right
            -1.0f,  1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f,  -1.0f,  0.0f,  0.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top-right
            // right face
            1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-right
            1.0f,  1.0f, -1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-left
            1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-left
            1.0f, -1.0f, -1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-left
            1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-right
            1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-right
            // bottom face
            -1.0f,  -1.0f, -1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top-left
             1.0f,  -1.0f , 1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom-right
             1.0f,  -1.0f, -1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right     
             1.0f,  -1.0f,  1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom-right
            -1.0f,  -1.0f, -1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top-left
            -1.0f,  -1.0f,  1.0f,  0.0f,  -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left      
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // bottom-left      
    };
    void InitQuad(gpu::FGPUState* InGPUState);
    void InitCube(gpu::FGPUState* InGPUState);

    void InitBasicShapes(gpu::FGPUState* InGPUState)
    {
        InitQuad(InGPUState);
        InitCube(InGPUState);
    }

    void InitQuad(gpu::FGPUState* InGPUState)
    {
        gpu::FBufferDescription bufferDescription;

        // sending vertex data
        bufferDescription.data = (void*)(BASIC_QUAD_VERTEX_DATA);
        bufferDescription.size = sizeof(BASIC_QUAD_VERTEX_DATA);

        gpu::CBuffer* QuadVertexBuffer = gpu::CreateBuffer(bufferDescription, gpu::EBufferUsage::STATIC, FString {"QuadVertexBuffer"}, InGPUState );

        FArray<gpu::FVertexAttribute> quadAttributes(4);
        quadAttributes.Add({ 0, 3, EType::FLOAT, false, sizeof(float) * 11, 0, 0 });
        quadAttributes.Add({ 1, 3, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 3), 0 });
        quadAttributes.Add({ 2, 3, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 6), 0 });
        quadAttributes.Add({ 3, 2, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 9), 0 });

        QuadVertexArray = gpu::CreateVertexArray(FString {"QuadVertexArray" }, InGPUState,  &quadAttributes, QuadVertexBuffer, nullptr, gpu::EDrawMode::TRIANGLE_STRIP, 4, 0);
        quadAttributes.Free();

        // we're not going to need the buffers on the CPU anymore, they have to be residient son the GPU tho, so we don't call Free()
        delete QuadVertexBuffer;
    };

    void InitCube(gpu::FGPUState* InGPUState)
    {
        gpu::FBufferDescription bufferDescription;

        // sending vertex data
        bufferDescription.data = (void*)(CUBE_VERTICES);
        bufferDescription.size = sizeof(CUBE_VERTICES);

        gpu::CBuffer* VertexBuffer = gpu::CreateBuffer(bufferDescription, gpu::EBufferUsage::STATIC,  FString{ "CubeVertexBuffer"}, InGPUState);

        FArray<gpu::FVertexAttribute> cubeAttributes(4);
        cubeAttributes.Add({ 0, 3, EType::FLOAT, false, sizeof(float) * 11, 0, 0 });
        cubeAttributes.Add({ 1, 3, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 3), 0 });
        cubeAttributes.Add({ 2, 3, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 6), 0 });
        cubeAttributes.Add({ 3, 2, EType::FLOAT, false, sizeof(float) * 11, (sizeof(float) * 9), 0 });

        CubeVertexArray = gpu::CreateVertexArray(FString {"CubeVertexArray" }, InGPUState, &cubeAttributes, VertexBuffer, nullptr, gpu::EDrawMode::TRIANGLES,
                                                 sizeof(CUBE_VERTICES) / (sizeof(float) * 11), 0);
        cubeAttributes.Free();

        // we're not going to need the buffers on the CPU anymore, they have to be residient on the GPU tho, so we don't call
        // Free()
        delete VertexBuffer;
    };
} // namespace lucid::misc