#include "RenderCommand.h"
#include "LogManager.h"

//  OpenGL
#ifdef __APPLE__
    #include <TargetConditionals.h>

    #if TARGET_OS_IPHONE
        #include <OpenGLES/ES3/gl.h>
    #else
        #include <OpenGL/gl3.h>
    #endif
#elif defined(__ANDROID__)
    #include <GLES3/gl3.h>
#else
    #include <GL/gl.h>
#endif

#include <cassert>

namespace RenderEngine
{
    namespace
    {
        GLuint _GetGLShaderType(ShaderType type)
        {
            switch (type)
            {
                case ShaderType::Vertex:
                    return GL_VERTEX_SHADER;
                case ShaderType::Fragment:
                    return GL_FRAGMENT_SHADER;
            }
            assert(false && "Unsupported shader type");
            return 0;
        }

        GLuint _GetGLBufferType(BufferType type)
        {
            switch (type)
            {
                case BufferType::Vertex:
                    return GL_ARRAY_BUFFER;
                case BufferType::Index:
                    return GL_ELEMENT_ARRAY_BUFFER;
            }
            assert(false && "Unsupported buffer type");
            return 0;
        }

        GLuint _GetTexFormat(TexFormat format)
        {
            switch (format)
            {
                case TexFormat::R:
                    return GL_RED;
                case TexFormat::RG:
                    return GL_RG;
                case TexFormat::RGB:
                    return GL_RGB;
                case TexFormat::RGBA:
                    return GL_RGBA;
            }
            assert(false && "Unsupported texture format");
            return GL_RGBA; 
        }

        GLuint _GetTexSurround(TexSurround surround)
        {
            switch (surround)
            {
                case TexSurround::Repeat:
                    return GL_REPEAT;
                case TexSurround::MirroredRepeat:
                    return GL_MIRRORED_REPEAT;
                case TexSurround::ClampToEdge:
                    return GL_CLAMP_TO_EDGE;
            }
            assert(false && "Unsupported texture surround mode");
            return GL_REPEAT; 
        }

        GLuint _GetTexWrap(TexWrap wrap)
        {
            switch (wrap)
            {
                case TexWrap::S:
                    return GL_TEXTURE_WRAP_S;
                case TexWrap::T:
                    return GL_TEXTURE_WRAP_T;
                case TexWrap::R:
                    return GL_TEXTURE_WRAP_R;
            }
            assert(false && "Unsupported texture wrap mode");
            return GL_TEXTURE_WRAP_S; 
        }

        GLuint _GetTexFilter(TexFilter filter)
        {
            switch (filter)
            {
                case TexFilter::MinFilter:
                    return GL_TEXTURE_MIN_FILTER;
                case TexFilter::MagFilter:
                    return GL_TEXTURE_MAG_FILTER;
            }
            assert(false && "Unsupported texture filter mode");
            return GL_TEXTURE_MIN_FILTER; // Default fallback
        }

        GLuint _GetTexFilterType(TexFilterType filterType)
        {
            switch (filterType)
            {
                case TexFilterType::Nearest:
                    return GL_NEAREST;
                case TexFilterType::Linear:
                    return GL_LINEAR;
                case TexFilterType::NearestMipmapNearest:
                    return GL_NEAREST_MIPMAP_NEAREST;
                case TexFilterType::LinearMipmapNearest:
                    return GL_LINEAR_MIPMAP_NEAREST;
                case TexFilterType::NearestMipmapLinear:
                    return GL_NEAREST_MIPMAP_LINEAR;
                case TexFilterType::LinearMipmapLinear:
                    return GL_LINEAR_MIPMAP_LINEAR;
            }
            assert(false && "Unsupported texture filter type");
            return GL_LINEAR; // Default fallback
        }
    }

    void RenderCommand::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RenderCommand::setViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void RenderCommand::setClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    unsigned int RenderCommand::createBuffer()
    {
        unsigned int bufferID;
        glGenBuffers(1, &bufferID);
        assert(bufferID != 0 && "Failed to create buffer");
        return bufferID;
    }

    void RenderCommand::destroyBuffer(unsigned int bufferID)
    {
        assert(bufferID != 0 && "Invalid buffer ID");
        glDeleteBuffers(1, &bufferID);
    }

    void RenderCommand::bindBuffer(BufferType type, unsigned int bufferID)
    {
        assert(bufferID != 0 && "Invalid buffer ID");
        glBindBuffer(_GetGLBufferType(type), bufferID);
    }

    void RenderCommand::unbindBuffer(BufferType type)
    {
        glBindBuffer(_GetGLBufferType(type), 0);
    }

    void RenderCommand::setBufferData(BufferType type, const void* data, size_t size)
    {
        assert(data != nullptr && "Data pointer is null");
        glBufferData(_GetGLBufferType(type), size, data, GL_STATIC_DRAW);
    }

    void RenderCommand::vertexAttribPointer(unsigned int index, int size, unsigned int stride, const void* pointer)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    unsigned int RenderCommand::createVertexArray()
    {
        unsigned int vaoID;
        glGenVertexArrays(1, &vaoID);
        assert(vaoID != 0 && "Failed to create vertex array");
        return vaoID;
    }

    void RenderCommand::destroyVertexArray(unsigned int vaoID)
    {
        assert(vaoID != 0 && "Invalid vertex array ID");
        glDeleteVertexArrays(1, &vaoID);
    }

    void RenderCommand::bindVertexArray(unsigned int vaoID)
    {
        assert(vaoID != 0 && "Invalid vertex array ID");
        glBindVertexArray(vaoID);
    }

    void RenderCommand::unbindVertexArray()
    {
        glBindVertexArray(0);
    }

    unsigned int RenderCommand::createShader(ShaderType type, const std::string& source)
    {
        unsigned int shaderID = glCreateShader(_GetGLShaderType(type));
        assert(shaderID != 0 && "Failed to create shader");

        const char* src = source.c_str();
        glShaderSource(shaderID, 1, &src, nullptr);
        glCompileShader(shaderID);

        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            LogManager::Log(LogLevel::Error, std::string(infoLog));
            LogManager::Log(LogLevel::Info, source);
            return 0;
        }

        return shaderID;
    }

    void RenderCommand::destroyShader(unsigned int shaderID)
    {
        assert(shaderID != 0 && "Invalid shader ID");
        glDeleteShader(shaderID);
    }

    unsigned int RenderCommand::createShaderProgram(const std::vector<unsigned int>& shaderIDs)
    {
        unsigned int programID = glCreateProgram();
        assert(programID != 0 && "Failed to create shader program");

        for (unsigned int shaderID : shaderIDs)
            glAttachShader(programID, shaderID);

        glLinkProgram(programID);

        int success;
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(programID, 512, nullptr, infoLog);
            LogManager::Log(LogLevel::Error, std::string(infoLog));
            return 0;
        }

        for (unsigned int shaderID : shaderIDs)
            glDetachShader(programID, shaderID);

        return programID;
    }

    void RenderCommand::destroyShaderProgram(unsigned int programID)
    {
        assert(programID != 0 && "Invalid shader program ID");
        glDeleteProgram(programID);
    }

    void RenderCommand::bindShaderProgram(unsigned int programID)
    {
        assert(programID != 0 && "Invalid shader program ID");
        glUseProgram(programID);
    }

    void RenderCommand::unbindShaderProgram()
    {
        glUseProgram(0);
    }

    int RenderCommand::getUniformLocation(unsigned int shaderProgram, const std::string& name)
    {
        assert(shaderProgram && "Shader Program is null!");
        int ret = glGetUniformLocation(shaderProgram, name.c_str());
        return ret;
    }

    void RenderCommand::setUniform1i(unsigned int locaID, int value)
    {
        glUniform1i(locaID, value);
    }

    void RenderCommand::setUniform1f(unsigned int locaID, float value)
    {
        glUniform1f(locaID, value);
    }

    unsigned int RenderCommand::createTexture()
    {
        unsigned int id = 0;
        glGenTextures(1, &id);
        assert(id != 0 && "Failed to create texture");
        return id;
    }

    void RenderCommand::destroyTexture(unsigned int textureID)
    {
        assert(textureID != 0 && "Invalid texture ID");
        glDeleteTextures(1, &textureID);
    }

    void RenderCommand::bindTexture(unsigned int textureID)
    {
        assert(textureID && "Texture is null!");
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void RenderCommand::unbindTexture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderCommand::activateTextureUnit(unsigned int unit)
    {
        assert(unit < 32 && "Texture unit out of range!");
        glActiveTexture(GL_TEXTURE0 + unit);
    }

    void RenderCommand::setTextureData(int width, int height, 
        TexFormat format, const void* data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, _GetTexFormat(format), width, height,
            0, _GetTexFormat(format), GL_UNSIGNED_BYTE, data);
    }

    void RenderCommand::setTextureWarpMode(TexWrap wrap, TexSurround surround)
    {
        glTexParameteri(GL_TEXTURE_2D, _GetTexWrap(wrap), _GetTexSurround(surround));
    }

    void RenderCommand::setTextureFilterMode(TexFilter filter, TexFilterType filterType)
    {
        glTexParameteri(GL_TEXTURE_2D, _GetTexFilter(filter), _GetTexFilterType(filterType));
    }

    void RenderCommand::drawArrays(unsigned int count)
    {
        assert(count > 0 && "Count must be greater than zero");
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void RenderCommand::drawElements(unsigned int count)
    {
        assert(count > 0 && "Count must be greater than zero");
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }
}
