#pragma once
#include <string>
#include <cstdint>
#include <unordered_map>
#include <exception>
#include <glm/gtc/type_ptr.hpp>
#include "engine/utils/error.hpp"
#include "engine/utils/types.hpp"
#include "engine/utils/imexp.hpp"
#include "engine/renderer/texture.hpp"

namespace bubble
{
class BUBBLE_ENGINE_EXPORT Shader
{
public:
    Shader() = default;

    Shader( const Shader& ) = delete;
    Shader& operator= ( const Shader& ) = delete;

    Shader( Shader&& ) noexcept;
    Shader& operator= ( Shader&& ) noexcept;

    i32 GetUni( const string& name ) const;

    void Bind() const;
    void Unbind() const;

    // lone i32 
    void SetUni1i( const string& name, const i32& val ) const;

    // f32 vec
    void SetUni1f( const string& name, const f32& val ) const;
    void SetUni2f( const string& name, const vec2& val ) const;
    void SetUni3f( const string& name, const vec3& val ) const;
    void SetUni4f( const string& name, const vec4& val ) const;

    // f32 matrices
    void SetUniMat3( const string& name, const mat3& val ) const;
    void SetUniMat4( const string& name, const mat4& val ) const;

    // textures
    void SetTexture2D( const string& name, i32 tex_id, i32 slot = 0 ) const;
    void SetTexture2D( const string& name, const Texture2D& texture, i32 slot = 0 ) const;
    void SetTexture2D( const string& name, const Ref<Texture2D>& texture, i32 slot = 0 ) const;

//private:
    string mName;
    GLuint  mShaderID;
    mutable std::unordered_map<string, i32> mUniformCache;
};

}