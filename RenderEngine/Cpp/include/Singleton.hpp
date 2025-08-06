#pragma once

#include <cassert>

namespace RenderEngine
{
    template <typename T>
    class Singleton
    {
    public:
        Singleton()
        {   
            assert(sInstance == nullptr && "Singleton instance already exists!");
            sInstance = static_cast<T*>(this);
        }

        ~Singleton()
        {
            assert(sInstance != nullptr && "Singleton instance does not exist!");
            sInstance = nullptr;
        }

        static T* Instance()
        {
            assert(sInstance != nullptr && "Singleton instance is not initialized!");
            return sInstance;
        }

    private:
        Singleton(Singleton&) = delete; 
        Singleton& operator=(Singleton&) = delete; 

    private:
        static inline T* sInstance = nullptr;
    };
}