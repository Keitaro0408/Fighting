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

SceneBase::SceneID GameScene::Control()
{

	return m_SceneID;
}

void GameScene::Draw()
{
}
