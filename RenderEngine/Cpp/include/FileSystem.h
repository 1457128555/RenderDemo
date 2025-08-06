#pragma once

#include "RenderProtocol.hpp"
#include <string>

namespace RenderEngine
{
    class FileSystem
    {
    public:
        static std::string ReadFile(const std::string& fileName);
        static std::string ReadShader(const std::string& fileName);

       static unsigned char* ReadImage(const std::string& fileName, 
        int& width, int& height, TexFormat& fmt, bool flipY);
       static void FreeImage(unsigned char* data);
    };
}