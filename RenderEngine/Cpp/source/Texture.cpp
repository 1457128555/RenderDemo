#include "Texture.h"

#include "RenderCommand.h"
#include "FileSystem.h"

namespace RenderEngine
{
    Texture::Texture(const std::string& fileName, bool flipY)
        : mFileName(fileName), mID(RenderCommand::Instance()->createTexture())
    {
        bind();
        RenderCommand::Instance()->setTextureWarpMode(TexWrap::S, TexSurround::Repeat);
        RenderCommand::Instance()->setTextureWarpMode(TexWrap::T, TexSurround::Repeat);
        RenderCommand::Instance()->setTextureWarpMode(TexWrap::R, TexSurround::Repeat);
        RenderCommand::Instance()->setTextureFilterMode(TexFilter::MinFilter, TexFilterType::Linear);
        RenderCommand::Instance()->setTextureFilterMode(TexFilter::MagFilter, TexFilterType::Linear);

        unsigned char* imageData = FileSystem::ReadImage(mFileName, mWidth, mHeight, mFormat, flipY);
        if (imageData)
        {
            RenderCommand::Instance()->setTextureData(mWidth, mHeight, mFormat, imageData);
        }  
        FileSystem::FreeImage(imageData); 
        
        unbind();
    }

    Texture::~Texture()
    {
        RenderCommand::Instance()->destroyTexture(mID);
    }

    void Texture::bind()const
    {
        RenderCommand::Instance()->bindTexture(mID);
    }

    void Texture::unbind()const
    {
        RenderCommand::Instance()->unbindTexture();
    }
} // namespace RenderEngine