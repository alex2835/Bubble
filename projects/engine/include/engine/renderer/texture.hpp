#pragma once
#include "engine/utils/error.hpp"
#include "engine/types/number.hpp"
#include "engine/types/glm.hpp"

namespace bubble
{
struct Texture2DSpecification
{
    u32 mWidth;
    u32 mHeight;
    u32 mChanelFormat;   // GL_UNSIGNED_BYTE, GL_FLOAT
    u32 mDataFormat;     // GL_RED, GL_RGB, GL_RGBA, GL_DEPTH_COMPONENT
    u32 mInternalFormat; // GL_RED8, GL_RGB8, GL_RGBA8, GL_DEPTH_COMPONENT
    u32 mMinFiler;       // GL_LINEAR, GL_NEAREST
    u32 mMagFilter;      // GL_LINEAR, GL_NEAREST
    u32 mWrapS;	         // GL_REPEAT, GL_CLAMP, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT 
    u32 mWrapT;	         // GL_REPEAT, GL_CLAMP, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT 
    vec4 mBorderColor;
    bool mFlip;
    bool mMinMap;
    bool mAnisotropicFiltering;

    Texture2DSpecification( const Texture2DSpecification& ) = default;

    void SetTextureSpecChanels( i32 channels );
    u32 ExtractTextureSpecChannels() const;
    u32 GetTextureSize() const;
    static Texture2DSpecification CreateRGBA8( uvec2 size );
    static Texture2DSpecification CreateRGBA32( uvec2 size );
    static Texture2DSpecification CreateObjectId( uvec2 size );
    static Texture2DSpecification CreateDepth( uvec2 size );
private:
    Texture2DSpecification( uvec2 size );
};



class Texture2D
{
public:
    Texture2D( const Texture2DSpecification& spec );
    Texture2D( const Texture2D& ) = delete;
    Texture2D& operator= ( const Texture2D& ) = delete;
    Texture2D( Texture2D&& ) noexcept;
    Texture2D& operator= ( Texture2D&& ) noexcept;
    ~Texture2D();
    
    void Swap( Texture2D& other ) noexcept;

    u32 RendererID() const;
    i32 Width()  const;
    i32 Height() const;

    // size in bytes
    void SetData( const void* data, u32 size );
    void GetData( void* data, u32 size ) const;

    void Bind( i32 slot = 0 ) const;
    static void UnbindAll();

    void Resize( const ivec2& new_size );
    void Invalidate();

    bool operator==( const Texture2D& other ) const;

private:
    u32 mRendererID = 0;
    Texture2DSpecification mSpecification;
};

}