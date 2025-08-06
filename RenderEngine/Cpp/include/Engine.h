
#pragma once

#include "Singleton.hpp"
#include <string>

namespace RenderEngine
{
    struct CreateEngineInfo
    {
        std::string assetPath = "Empty/";
    };

    class Engine : public Singleton<Engine>
    {
    public:
        explicit Engine(const CreateEngineInfo& info);
        ~Engine();
        
        void renderOneFrame();

        void setScreenSize(int width, int height);

        class Scene*        getScene()            { return mScenePtr; }
        unsigned int        getFrameNum()   const { return mFrameNum; }
        const std::string&  getAssetPath()  const { return mInfo.assetPath; }

    private:
        CreateEngineInfo mInfo;

        int mScreenWidth  = 0;
        int mScreenHeight = 0;

        unsigned int mFrameNum = 0;

        class Scene* mScenePtr = nullptr;
    };
}
