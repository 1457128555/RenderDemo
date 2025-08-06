#pragma once

namespace RenderEngine
{
    enum class ShaderType : unsigned int
    {
        Vertex          = 0,
        Fragment,
    };

    enum class BufferType : unsigned int
    {
        Vertex          = 0,
        Index,
    };

    enum class TexFormat : unsigned int
    {
        R               = 0,
        RG,
        RGB,
        RGBA,
    };

    enum class TexSurround : unsigned int
    {
        Repeat          = 0,       
        MirroredRepeat,      
        ClampToEdge,       
    };

    enum class TexWrap : unsigned int
    {
        S               = 0,       
        T,       
        R ,       
    };

    enum class TexFilter : unsigned int
    {
        MinFilter       = 0,       
        MagFilter,       
    };

    enum class TexFilterType : unsigned int
    {
        Nearest         = 0,   
        Linear,   
        NearestMipmapNearest,   
        LinearMipmapNearest,   
        NearestMipmapLinear,   
        LinearMipmapLinear,   
    };
}