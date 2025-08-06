#pragma once

#include <memory>

namespace RenderEngine
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        void renderOneFrame();

        void onPlayBottom();
        void setLutIntensity(float value);

        void setRenderFlag(bool flag);
        
    private:
        struct _Pirvate;
        std::unique_ptr<_Pirvate> _dp; 

    private:
        Scene(Scene&) = delete;
        Scene& operator=(Scene&) = delete;
    };
}
