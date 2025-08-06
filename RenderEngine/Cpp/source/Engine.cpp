#include "Engine.h"

#include "RenderCommand.h"
#include "Scene.h"

namespace RenderEngine
{
    Engine::Engine(const CreateEngineInfo& info)
        : mInfo(info)
    {
        new RenderCommand;
        mScenePtr = new Scene;
    }
    
    Engine::~Engine()
    {
        if(mScenePtr)
        {
            delete mScenePtr;
            mScenePtr = nullptr;
        }

        delete RenderCommand::Instance();
    }
    
    void Engine::renderOneFrame()
    {
        if(mScenePtr)
            mScenePtr->renderOneFrame();
        mFrameNum++;
    }

    void Engine::setScreenSize(int width, int height)
    {
        mScreenWidth = width;
        mScreenHeight = height;
        RenderCommand::Instance()->setViewport(mScreenWidth, mScreenHeight);
    }
}
