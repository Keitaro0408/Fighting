/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
}

GameScene::~GameScene()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

SceneBase::SceneID GameScene::Update()
{

	return m_SceneID;
}

void GameScene::Draw()
{
}
