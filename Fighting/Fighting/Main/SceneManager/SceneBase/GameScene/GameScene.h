/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "..\SceneBase.h"

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public SceneBase
{
public:
	/**
	 * コンストラクタ
	 */
	GameScene();

	/**
	 * デストラクタ
	 */
	virtual ~GameScene();

	/**
	 * 制御関数
	 * @return シーンの遷移先ID
	 */
	virtual SceneID Update();

	/**
	 * 描画関数
	 */
	virtual void Draw();

private:
	GameScene(const GameScene&);
	void operator=(const GameScene&);

};


#endif
