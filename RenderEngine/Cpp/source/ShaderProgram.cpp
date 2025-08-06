#include "ShaderProgram.h"
#include "RenderCommand.h"

#include <cassert>

namespace RenderEngine
{
    namespace
    {
        class Shader
        {
        public:
            Shader(ShaderType type, const std::string& source)
                : mType(type), mSource(source), mID(RenderCommand::Instance()->createShader(type, source))
            {
                assert(mID != 0 && "Failed to create shader");
            }

            ~Shader()
            {
                RenderCommand::Instance()->destroyShader(mID);
            }

            unsigned int getID() const { return mID; }

        private:
            const ShaderType    mType;
            const std::string   mSource;
            const unsigned int  mID = 0u;   

        private:        
            Shader(Shader&) = delete;
            Shader& operator=(Shader&) = delete;
        };
    }

    ShaderProgram::ShaderProgram(const std::string& vertexSource, 
        const std::string& fragmentSource)
    {
        Shader vertexShader(ShaderType::Vertex, vertexSource);
        Shader fragmentShader(ShaderType::Fragment, fragmentSource);

        mID = RenderCommand::Instance()->createShaderProgram({vertexShader.getID(), fragmentShader.getID()});
        assert(mID != 0 && "Failed to create shader program");
    }

    ShaderProgram::~ShaderProgram()
    {
        RenderCommand::Instance()->destroyShaderProgram(mID);
    }

    void ShaderProgram::bind() const
    {
        assert(mID != 0 && "ShaderProgram ID is not initialized.");
        RenderCommand::Instance()->bindShaderProgram(mID);
    }

    void ShaderProgram::unbind() const
    {
        RenderCommand::Instance()->unbindShaderProgram();
    }

    void ShaderProgram::setUniform1i(const std::string& name, int value) const
    {
        int location = RenderCommand::Instance()->getUniformLocation(mID, name);
        if (location != -1)
            RenderCommand::Instance()->setUniform1i(location, value);
    }

    void ShaderProgram::setUniform1f(const std::string& name, float value) const
    {
        int location = RenderCommand::Instance()->getUniformLocation(mID, name);
        if (location != -1)
            RenderCommand::Instance()->setUniform1f(location, value);
    }
}