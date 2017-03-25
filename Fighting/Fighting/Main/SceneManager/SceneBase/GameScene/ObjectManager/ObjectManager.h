/**
 * @file   ObjectManager.h
 * @brief  ObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <memory>

class GameObjectManager;
class UIManager;

class ObjectManager
{
public:
	/**
	 * コンストラクタ
	 */
	ObjectManager();

	/**
	 * デストラクタ
	 */
	~ObjectManager();

	/**
	 * 制御関数
	 */
	void Update();

	/**
	 * 描画関数
	 */
	void Draw();

private:
	std::unique_ptr<GameObjectManager> m_pGameObjectManager;
	std::unique_ptr<UIManager>		   m_pUIManager;

};


#endif
