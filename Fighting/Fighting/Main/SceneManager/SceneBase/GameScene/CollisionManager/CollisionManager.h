/**
 * @file   CollisionManager.h
 * @brief  CollisionManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "Singleton.h"
#include <vector>

class CollisionData;

class CollisionManager
{
	friend Lib::Singleton<CollisionManager>;
public:
	/**
	 * 当たり判定の追加
	 * @param[in] _pCollisionData 追加する当たり判定
	 */
	void AddCollision(CollisionData* _pCollisionData);

	/**
	 * 判定の更新
	 * @param[in] _index 当たり判定を更新するindex
	 */
	void Update(int _index);

private:
	CollisionManager() = default;
	~CollisionManager() = default;

	std::vector<CollisionData*> m_pCollisionData;

};


#endif
