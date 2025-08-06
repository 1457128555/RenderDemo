#include "LogManager.h"

#include <iostream>

namespace RenderEngine
{
    namespace
    {
        void _OutputLog(const std::string& message)
        {
            std::cout << message << std::endl;
        }
    }

    void LogManager::Log(LogLevel level, const std::string& message)
    {
        switch (level)
        {
            case LogLevel::Info:
                _OutputLog("[INFO]: " + message);
                break;
            case LogLevel::Warning:
                _OutputLog("[WARNING]: " + message);
                break;
            case LogLevel::Error:
                _OutputLog("[ERROR]: " + message);
                break;
        }
    }
} // namespace RenderEngine
