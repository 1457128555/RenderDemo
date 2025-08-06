#include "RenderEngine.h"
#include "Engine.h"
#include "Scene.h"

using namespace RenderEngine;

void initRenderEngine(const char* assetPath) 
{
    CreateEngineInfo info = {
        .assetPath = std::string(assetPath) // Convert C string to std::string
    };
    new Engine(info);
}

void renderOneFrame() 
{
    Engine::Instance()->renderOneFrame();
}

void quitRenderEngine() 
{
    delete Engine::Instance();
}

void setScreenSize(int width, int height)
{
    Engine::Instance()->setScreenSize(width, height);
}

void onPlayBottom()
{
    Engine::Instance()->getScene()->onPlayBottom();
}

void setLutIntensity(float value)
{
    Engine::Instance()->getScene()->setLutIntensity(value);
}
