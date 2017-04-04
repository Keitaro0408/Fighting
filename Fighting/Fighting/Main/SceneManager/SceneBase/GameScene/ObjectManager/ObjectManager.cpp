/**
 * @file   ObjectManager.cpp
 * @brief  ObjectManagerクラスの実装
 * @author kotani
 */
#include "ObjectManager.h"
#include "GameObjectManager\GameObjectManager.h"
#include "UIManager\UIManager.h"


ObjectManager::ObjectManager() :
m_pGameObjectManager(new GameObjectManager()),
m_pUIManager(new UIManager())
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Update()
{
	m_pGameObjectManager->Update();
}

void ObjectManager::Draw()
{
	m_pGameObjectManager->Draw();
}
