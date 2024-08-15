#pragma once
#include "engine/log/log.hpp"
#include "engine/utils/types.hpp"
#include "engine/utils/filesystem.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/renderer/model.hpp"
#include "engine/renderer/skybox.hpp"
#include <mutex>

struct aiMesh;
struct aiNode;
struct aiScene;
struct aiMaterial;

namespace bubble
{
// Object id shader to select entity from screen
constexpr string_view OBJECT_PICKING_SHADER = "./resources/shaders/object_picking"sv;
constexpr string_view WHITE_SHADER = "./resources/shaders/white"sv;
constexpr string_view PHONG_SHADER = "./resources/shaders/phong"sv;
constexpr string_view ONLY_DEFUSE_TEXTURE_SHADER = "./resources/shaders/only_defuse_texture"sv;
constexpr string_view ONLY_DEFUSE_COLOR_SHADER = "./resources/shaders/only_defuse_color"sv;

struct TextureData
{
    Scope<u8[]> mData;
    Texture2DSpecification mSpec;
    path mPath;
};

TextureData OpenTexture( const path& path );

Ref<Texture2D> LoadTexture2D( const path& path );
Ref<Texture2D> LoadTexture2D( const TextureData& textureData );

Ref<Shader> LoadShader( const path& path );
Ref<Model> LoadModel( const path& path );
Ref<Model> LoadModel( const TextureData& path );
Ref<Skybox> LoadSkybox( const path& path );


struct Loader
{
    hash_map<path, Ref<Texture2D>> mTextures;
    hash_map<path, Ref<Model>> mModels;
    hash_map<path, Ref<Shader>> mShaders;
    hash_map<path, Ref<Skybox>> mSkyboxes;
    
    Ref<Texture2D> LoadTexture2D( const path& path );
    void LoadTextures2D( const vector<path>& paths );
    Ref<Shader> LoadShader( const path& path );
    Ref<Model> LoadModel( const path& path );
    void LoadModels( const vector<path>& paths );
    Ref<Skybox> LoadSkybox( const path& path );
};

}