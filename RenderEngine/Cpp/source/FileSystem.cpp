#include "FileSystem.h"
#include "LogManager.h"
#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <fstream>
#include <sstream>

namespace RenderEngine
{
    namespace
    {
        TexFormat _GetTexFormat(int channels)
        {
            switch (channels)
            {
                case 1: return TexFormat::R;
                case 2: return TexFormat::RG;
                case 3: return TexFormat::RGB;
                case 4: return TexFormat::RGBA;
            }
            assert(false && "Unsupported number of channels for texture format!");
            return TexFormat::RGBA; // Default fallback
        }
    }


    std::string FileSystem::ReadFile(const std::string& fileName)
    {
        std::string fullPath = Engine::Instance()->getAssetPath() + "/" + fileName;

        std::string data;
        std::ifstream file(fullPath, std::ios::binary);
        if (!file.is_open())
            LogManager::Log(LogLevel::Error, "Failed to open file: " + fullPath);
        else
        {
            data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
        }
        
        return data;
    }

    std::string FileSystem::ReadShader(const std::string& fileName)
    {
        return ReadFile("Shader/" + fileName);
    }

    unsigned char* FileSystem::ReadImage(const std::string& fileName, 
        int& width, int& height, TexFormat& fmt, bool flipY)
    {
        const std::string imageData = ReadFile("Texture/" + fileName);
        int channels = 0;
        stbi_set_flip_vertically_on_load(flipY);
        unsigned char* data = stbi_load_from_memory((const stbi_uc*)imageData.data(), 
            (int)imageData.size(), &width, &height, &channels, 0);

        if(data)
            fmt = _GetTexFormat(channels);
        return data;
    }

    void FileSystem::FreeImage(unsigned char* data)
    {
        if(data)
            stbi_image_free(data);
    }
}