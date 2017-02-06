/*
* Copyright (C) 2017 by Grapefruit Tech
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include <vorpal/VorpalEngine.hpp>
#include <vorpal/utility/Logger.hpp>
#include <vorpal/graphics/Graphics.hpp>
#include <vorpal/graphics/Camera.hpp>
#include <vorpal/graphics/SceneGraph.hpp>
#include <vorpal/utility/asset/SimpleStorage.hpp>
#include <vorpal/system/Window.hpp>
namespace vp
{
VorpalEngine::VorpalEngine()
        : m_pSceneGraph(nullptr),
        m_isInitialized(false), 
        m_pWindow(nullptr),
        m_pGraphics(nullptr)
        //m_pCamera(nullptr)
    {
    }

VorpalEngine::~VorpalEngine()
{
    Deinit();
}

bool VorpalEngine::Init()
{
    if (m_isInitialized)
    {
        return false;
    }

    vp::utility::asset::SimpleStorage::Instance();
    LOG_INFO("Engine initialization started.");
    m_pWindow = new system::Window;
    m_pGraphics = new graphics::Graphics;
    //m_pCamera = new graphics::Camera;
    m_pSceneGraph = new graphics::SceneGraph;

    if (!m_pWindow->Init())
    {
        Deinit();
        return false;
    }

    if (!m_pGraphics->Init())
    {
        Deinit();
        return false;
    }

    m_isInitialized = true;

    LOG_INFO("Engine initialization finished.");

    return true;
}

void VorpalEngine::Deinit()
{
    if (m_pGraphics)
    {
        m_pGraphics->Deinit();
        delete m_pGraphics;
        m_pGraphics = nullptr;
    }

    if (m_isInitialized)
    {
        LOG_INFO("Engine shutdown correctly.");
    }

    m_isInitialized = false;
}

void VorpalEngine::Run()
{
    while (!m_pWindow->ShouldClose())
    {
        m_pWindow->RetrieveEvents();
        m_pGraphics->Render();
    }
}
}
