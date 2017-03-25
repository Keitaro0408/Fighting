/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "Window.h"
#include "TextureManager.h"
#include "DSoundManager.h"
#include "KeyDevice.h"
#include "DX11Manager.h"
#include "ObjectManager\ObjectManager.h"

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	{
		HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();

		// Lib::DX11Manager
		SINGLETON_CREATE(Lib::DX11Manager);
		SINGLETON_INSTANCE(Lib::DX11Manager).Init(hWnd);
		// end

		// Lib::DSoundManager
		SINGLETON_CREATE(Lib::DSoundManager);
		SINGLETON_INSTANCE(Lib::DSoundManager).Init(hWnd);
		// end
	}

	{
		ID3D11Device* pDevice = SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice();

		// Lib::TextureManager
		SINGLETON_CREATE(Lib::TextureManager);
		SINGLETON_INSTANCE(Lib::TextureManager).Init(pDevice);
		// end
	}

	m_pObjectManager.reset(new ObjectManager());
}

GameScene::~GameScene()
{
	m_pObjectManager.reset();

	// Lib::TextureManager
	SINGLETON_INSTANCE(Lib::TextureManager).Release();
	SINGLETON_DELETE(Lib::TextureManager);
	// end

	// Lib::DSoundManager
	SINGLETON_INSTANCE(Lib::DSoundManager).Release();
	SINGLETON_DELETE(Lib::DSoundManager);
	// end

	// Lib::DX11Manager
	SINGLETON_INSTANCE(Lib::DX11Manager).Release();
	SINGLETON_DELETE(Lib::DX11Manager);
	// end
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID GameScene::Update()
{
	m_pObjectManager->Update();
	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_pObjectManager->Draw();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}
