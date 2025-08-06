#pragma once

#include <string>
#include <memory>

namespace RenderEngine
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ~ShaderProgram();

        void bind()     const;
        void unbind()   const;

        void setUniform1i(const std::string& name, int value)   const;
        void setUniform1f(const std::string& name, float value) const;
    private:
        unsigned int mID = 0u;

    public:
        using type_value = ShaderProgram;
        
        using _Tp   = type_value;
        using _Ptr  = _Tp*; 
        using _SPtr = std::shared_ptr<_Tp>;
        using _UPtr = std::unique_ptr<_Tp>;
    };
}