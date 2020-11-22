#version 330 core

#include "material.glsl"

uniform FlatMaterial uMaterial;

out vec4 oFragColor;

void main()
{
    oFragColor = vec4(uMaterial.Color, 1.0);
}