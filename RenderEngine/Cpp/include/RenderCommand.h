#pragma once

#include "RenderProtocol.hpp"
#include "Singleton.hpp"

#include <string>
#include <vector>

namespace RenderEngine
{
    class RenderCommand : public Singleton<RenderCommand>
    {
    public:

        void clear();

        //  GL Render State
        void setViewport(int width, int height);
        void setClearColor(float r, float g, float b, float a);

        //  Render Buffer
        unsigned int createBuffer();
        void destroyBuffer(unsigned int bufferID);

        void bindBuffer(BufferType type, unsigned int bufferID);
        void unbindBuffer(BufferType type);
        void setBufferData(BufferType type, const void* data, size_t size);

        void vertexAttribPointer(unsigned int index, int size, unsigned int stride, const void* pointer);

        unsigned int createVertexArray();
        void destroyVertexArray(unsigned int vaoID);
        void bindVertexArray(unsigned int vaoID);
        void unbindVertexArray();

        //  Shader Program
        unsigned int createShader(ShaderType type, const std::string& source);
        void destroyShader(unsigned int shaderID);

        unsigned int createShaderProgram(const std::vector<unsigned int>& shaderIDs);
        void destroyShaderProgram(unsigned int programID);
    
        void bindShaderProgram(unsigned int programID);
        void unbindShaderProgram();

        int  getUniformLocation(unsigned int shaderProgram, const std::string& name);
        void setUniform1i(unsigned int locaID, int value);
        void setUniform1f(unsigned int locaID, float value);

        //  Texture
        unsigned int createTexture();
        void destroyTexture(unsigned int textureID);
        void bindTexture(unsigned int textureID);
        void unbindTexture();

        void activateTextureUnit(unsigned int unit);

        void setTextureData(int width, int height, TexFormat format, const void* data);

        void setTextureWarpMode(TexWrap wrap, TexSurround surround);
        void setTextureFilterMode(TexFilter filter, TexFilterType filterType);
       
        //  Draw Calls
        void drawArrays(unsigned int count);
        void drawElements(unsigned int count);
    };
}