/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#include <vector>
#include <memory>

class CombatManager;
class ObjecBase;

/**
 * ゲームのUI以外のオブジェクト管理
 */
class GameObjectManager
{
public:
	/**
	 * コンストラクタ
	 */
	GameObjectManager();

	/**
	 * デストラクタ
	 */
	~GameObjectManager();

	/**
	 * 更新関数
	 */
	void Update();

	/**
	 * 描画関数
	 */
	void Draw();

private:
	GameObjectManager(const GameObjectManager&);
	void operator=(const GameObjectManager&);

	std::shared_ptr<CombatManager>			 m_pCombatManager;
	std::vector<std::unique_ptr<ObjecBase> > m_pObjectBase;

};


#endif
