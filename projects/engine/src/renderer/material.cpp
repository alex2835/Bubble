
#include "engine/renderer/material.hpp"

namespace bubble
{

void BasicMaterial::Apply( const Ref<Shader>& shader ) const
{
    shader->Bind();
    shader->SetUni4f( "uMaterial.diffuse_color", mDiffuseColor );
    shader->SetUni3f( "uMaterial.specular_coef", mSpecularCoef );
    shader->SetUni3f( "uMaterial.ambient_coef", mAmbientCoef );

    // Textures
    shader->SetUni1i( "uMaterial.diffuse_map", 0 );
    mDiffuseMap->Bind( 0 );

    if ( mSpecularMap )
    {
        shader->SetUni1i( "uMaterial.specular_map", 1 );
        mSpecularMap->Bind( 1 );
    }

    if( mNormalMap )
    {
        shader->SetUni1i( "uMaterial.normal_map", 2 );
        mNormalMap->Bind( 2 );
    }

    shader->SetUni1i( "uMaterial.shininess", mShininess );
    shader->SetUni1i( "uNormalMapping", (bool)mNormalMap );
    shader->SetUni1f( "uNormalMappingStrength", mNormalMapStrength );
}

//ExtendedMaterial::ExtendedMaterial( vector<Ref<Texture2D>>&& diffuse_maps,
//                                    vector<Ref<Texture2D>>&& specular_maps,
//                                    vector<Ref<Texture2D>>&& normal_maps,
//                                    i32 shininess )
//    : mDiffuseMaps( std::move( diffuse_maps ) ),
//      mSpecularMaps( std::move( specular_maps ) ),
//      mNormalMaps( std::move( normal_maps ) ),
//      mShininess( shininess )
//{
//}
//
//void ExtendedMaterial::Set( const Ref<Shader>& shader ) const
//{
//    i32 slot = 0;
//    for( i32 i = 0; i < mDiffuseMaps.size(); i++ )
//    {
//        shader->SetUni1i( "uMaterial.diffuse" + std::to_string( i ), slot );
//        mDiffuseMaps[i]->Bind( slot++ );
//    }
//
//    for( i32 i = 0; i < mSpecularMaps.size(); i++ )
//    {
//        shader->SetUni1i( "uMaterial.specular" + std::to_string( i ), slot );
//        mSpecularMaps[i]->Bind( slot++ );
//    }
//
//    for( i32 i = 0; i < mNormalMaps.size(); i++ )
//    {
//        shader->SetUni1i( "uMaterial.normal" + std::to_string( i ), slot );
//        mNormalMaps[i]->Bind( slot++ );
//    }
//
//    shader->SetUni1i( "uMaterial.shininess", mShininess );
//    shader->SetUni1i( "u_NormalMapping", static_cast<i32>( mNormalMaps.size() ) );
//}

}