#pragma once
#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_containers.hpp>
#include "engine/utils/error.hpp"
#include "engine/types/number.hpp"
#include "engine/types/pointer.hpp"
#include "engine/types/string.hpp"
#include "engine/types/map.hpp"
#include "engine/utils/filesystem.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/buffer.hpp"

namespace bubble
{
enum class ShaderModule
{
    None,
    Material,
    Light,
};
using ShaderModules = magic_enum::containers::bitset<ShaderModule>;


class Shader
{
public:
    Shader() = default;

    Shader( const Shader& ) = delete;
    Shader& operator= ( const Shader& ) = delete;

    Shader( Shader&& ) noexcept;
    Shader& operator= ( Shader&& ) noexcept;

    void Swap( Shader& other ) noexcept;

    i32 GetUniform( string_view name ) const;
    i32 GetUniformBuffer( string_view name ) const;

    void Bind() const;
    void Unbind() const;

    // lone i32
    void SetUni1i( string_view name, const i32& val ) const;
    void SetUni1ui( string_view name, const u32& val ) const;

    // f32 vec
    void SetUni1f( string_view name, const f32& val ) const;
    void SetUni2f( string_view name, const vec2& val ) const;
    void SetUni3f( string_view name, const vec3& val ) const;
    void SetUni4f( string_view name, const vec4& val ) const;

    // f32 matrices
    void SetUniMat3( string_view name, const mat3& val ) const;
    void SetUniMat4( string_view name, const mat4& val ) const;

    // textures
    void SetTexture2D( string_view name, i32 tex_id, i32 slot = 0 ) const;
    void SetTexture2D( string_view name, const Texture2D& texture, i32 slot = 0 ) const;
    void SetTexture2D( string_view name, const Ref<Texture2D>& texture, i32 slot = 0 ) const;

    // Uniform buffer
    void SetUniformBuffer( const Ref<UniformBuffer>& ub );

    string mName;
    path mPath;
    ShaderModules mModules;
    u32 mShaderId = 0;
private:
    mutable str_hash_map<i32> mUniformCache;
};

}