#pragma once
#include "engine/types/glm.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/shader.hpp"

namespace bubble
{

struct BasicMaterial
{
    BasicMaterial() = default;
    BasicMaterial( const BasicMaterial& ) = delete;
    BasicMaterial& operator=( const BasicMaterial& ) = delete;
    BasicMaterial( BasicMaterial&& ) = default;
    BasicMaterial& operator=( BasicMaterial&& ) = default;

    void Apply( const Ref<Shader>& shader ) const;

    Ref<Texture2D> mDiffuseMap;
    Ref<Texture2D> mSpecularMap;
    Ref<Texture2D> mNormalMap;
    vec4 mDiffuseColor = vec4( 1.0f );
    vec4 mAmbient = vec4( vec3( 0.1f ), 1.0f );
    vec4 mSpecular = vec4( vec3( 0.1f ), 1.0f );
    vec4 mEmission = vec4( 0.0f );
    i32 mShininess = 32;
    f32 mShininessStrength = 1.0f;
    f32 mNormalMapStrength = 0.1f;
};

// PBR material
// ...

}