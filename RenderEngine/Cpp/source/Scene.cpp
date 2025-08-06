#include "Scene.h"

#include "Engine.h"
#include "RenderCommand.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include "FileSystem.h"
#include "LogManager.h"

#include <thread>
#include <chrono>

namespace RenderEngine
{
    namespace
    {
        float vertices[] = {
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
        };
        unsigned int indices[] = {  
            0, 1, 3, 
            1, 2, 3,  
        };
    }

    struct Scene::_Pirvate
    {
        unsigned int            mVAO = 0;
        unsigned int            mVBO = 0;
        unsigned int            mEBO = 0;

        ShaderProgram::_UPtr    mShaderProgram;

        Texture::_UPtr          mBaseTable;
        std::vector<Texture::_UPtr> mTexArray;
        
        float mLutIntensity = 0.f;
        bool  mPlayFlag = true;

        bool  mRenderFlag = true; 
    };

    Scene::Scene() : _dp(new _Pirvate)
    {
        RenderCommand::Instance()->setClearColor(0.f, 0.f, 0.f, 1.0f);

        std::string vertexShaderSource = FileSystem::ReadShader("RenderDemo.vert");
        std::string fragmentShaderSource = FileSystem::ReadShader("RenderDemo.frag");
        _dp->mShaderProgram = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
        
        _dp->mBaseTable = std::make_unique<Texture>("baseTable.png", false);
        for(int i = 1; i <= 50; i++)
        {
            const std::string texName = "Medium/medium_" + std::to_string(i) + ".png";
            _dp->mTexArray.emplace_back(std::make_unique<Texture>(texName));
        }

        _dp->mVAO = RenderCommand::Instance()->createVertexArray();
        RenderCommand::Instance()->bindVertexArray(_dp->mVAO);

        _dp->mVBO = RenderCommand::Instance()->createBuffer();
        RenderCommand::Instance()->bindBuffer(BufferType::Vertex, _dp->mVBO);
        RenderCommand::Instance()->setBufferData(BufferType::Vertex, vertices, sizeof(vertices));

        _dp->mEBO = RenderCommand::Instance()->createBuffer();
        RenderCommand::Instance()->bindBuffer(BufferType::Index, _dp->mEBO);
        RenderCommand::Instance()->setBufferData(BufferType::Index, indices, sizeof(indices));

        RenderCommand::Instance()->vertexAttribPointer(0, 3, 5 * sizeof(float), (void*)0);
        RenderCommand::Instance()->vertexAttribPointer(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        RenderCommand::Instance()->unbindBuffer(BufferType::Vertex);
        RenderCommand::Instance()->unbindVertexArray();
    }

    Scene::~Scene()
    {
        RenderCommand::Instance()->destroyVertexArray(_dp->mVAO);
        RenderCommand::Instance()->destroyBuffer(_dp->mVBO);
        RenderCommand::Instance()->destroyBuffer(_dp->mEBO);
    }

    void Scene::renderOneFrame()
    {
        static unsigned int sPlayFrameNum = 0u;
        const unsigned int texIndex = sPlayFrameNum % _dp->mTexArray.size();
        Texture::_UPtr& curTex = _dp->mTexArray.at(texIndex);

        RenderCommand::Instance()->clear();

        _dp->mShaderProgram->bind();

        _dp->mShaderProgram->setUniform1i("uImageTex", 0);
        RenderCommand::Instance()->activateTextureUnit(0);
        curTex->bind();

        _dp->mShaderProgram->setUniform1i("uBaseTableTex", 1);
        RenderCommand::Instance()->activateTextureUnit(1);
        _dp->mBaseTable->bind();

        _dp->mShaderProgram->setUniform1f("uLutIntensity", _dp->mLutIntensity);

        RenderCommand::Instance()->bindVertexArray(_dp->mVAO);
        RenderCommand::Instance()->drawElements(6);
        RenderCommand::Instance()->unbindVertexArray();

        curTex->unbind();
        _dp->mBaseTable->unbind();
        _dp->mShaderProgram->unbind();
        
        if(_dp->mPlayFlag && _dp->mRenderFlag)
            sPlayFrameNum++;
    }

    void Scene::setLutIntensity(float value)
    {
        _dp->mLutIntensity = value;
    }

    void Scene::onPlayBottom()
    {
        setRenderFlag(false);

        // Do somethings
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            _dp->mPlayFlag = !_dp->mPlayFlag;
        }

        setRenderFlag(true);
    }

    void Scene::setRenderFlag(bool flag)
    {
        _dp->mRenderFlag = flag;
    }
}
