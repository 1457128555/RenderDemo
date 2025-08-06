#pragma once

#include <string>

namespace RenderEngine
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    class LogManager
    {
    public:
        static void Log(LogLevel level, const std::string& message);
    };
}