#pragma once
#include <cstdint>
#include <cassert>
#include "engine/utils/imexp.hpp"
#include "engine/utils/types.hpp"
#include "engine/window/window.hpp"
#include "engine/renderer/texture.hpp"

namespace bubble
{
struct BUBBLE_ENGINE_EXPORT FramebufferSpecification
{
    GLsizei mWidth = 0;
    GLsizei mHeight = 0;
    GLsizei mSamples = 1;

    uvec2 Size() const
    {
        return { mWidth, mHeight };
    }
};


class BUBBLE_ENGINE_EXPORT Framebuffer
{
public:
    Framebuffer() = delete;
    Framebuffer( const Framebuffer& ) = delete;
    Framebuffer& operator= ( const Framebuffer& ) = delete;
    Framebuffer( Framebuffer&& other ) noexcept;
    Framebuffer& operator = ( Framebuffer&& other ) noexcept;
    Framebuffer( Texture2D&& color, Texture2D&& depth );
    ~Framebuffer();

    void Swap( Framebuffer& other ) noexcept;

    void SetColorAttachment( Texture2D&& texture );
    void SetDepthAttachment( Texture2D&& texture );
    void SetStencilAttachment( Texture2D&& texture );
    Texture2D& ColorAttachment();
    Texture2D& DepthAttachment();
    opt<Texture2D>& StencilAttachment();

    u32 ReadColorAttachmentPixelRedUint( uvec2 pos );
    
    void Bind() const;
    void Unbind() const;
    static void BindWindow( Window& window );
    void Invalidate();

    GLsizei Width() const;
    GLsizei Height() const;
    uvec2 Size() const;
    void Resize( uvec2 size );

    FramebufferSpecification Specification() const;

private:
    GLuint mRendererID = 0;
    Texture2D mColorAttachment;
    Texture2D mDepthAttachment;
    opt<Texture2D> mStencilAttachment;
    FramebufferSpecification mSpecification;
};
}