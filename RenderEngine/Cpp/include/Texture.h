#pragma once

#include "RenderProtocol.hpp"

#include <string>
#include <memory>

namespace RenderEngine
{
    class Texture
    {
    public:
        explicit Texture(const std::string& fileName, bool flipY = true);
        ~Texture();

        void bind()     const;
        void unbind()   const;
    
    private:
        const std::string mFileName;
        const unsigned int mID = 0u;

        int mWidth = 0;
        int mHeight = 0;
        TexFormat mFormat = TexFormat::RGBA; 

    private:
        Texture(Texture&) = delete;
        Texture& operator=(Texture&) = delete;
    
    public:
        using type_value = Texture;
        
        using _Tp   = type_value;
        using _Ptr  = _Tp*; 
        using _SPtr = std::shared_ptr<_Tp>;
        using _UPtr = std::unique_ptr<_Tp>;
    };
}
