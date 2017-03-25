/**
 * @file   GameObjectManager.cpp
 * @brief  GameObjectManagerクラスの実装
 * @author kotani
 */
#include "GameObjectManager.h"
#include "../ObjectBase/ObjecBase.h"
#include "BackGround\BackGround.h"


GameObjectManager::GameObjectManager()
{
	m_pObjectBase.push_back(std::unique_ptr<BackGround>(new BackGround()));
}

GameObjectManager::~GameObjectManager()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void GameObjectManager::Update()
{
	for (unsigned int i = 0; i < m_pObjectBase.size(); i++)
	{
		m_pObjectBase[i]->Update();
	}
}

void GameObjectManager::Draw()
{
	for (unsigned int i = 0; i < m_pObjectBase.size(); i++)
	{
		m_pObjectBase[i]->Draw();
	}
}

