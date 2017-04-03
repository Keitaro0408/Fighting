#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H
#include <D3DX10.h>
#include "Singleton.h"


/**
 * 戦闘を管理するクラス
 */
class CombatManager
{
	friend Lib::Singleton<CombatManager>;
public:
	/**
	 * プレイヤーの座標のセット
	 * @param[in] _playerPos プレイヤーの座標
	 */
	inline void SetPlayerPos(D3DXVECTOR2* _playerPos)
	{
		m_PlayerPos = *_playerPos;
	}

	D3DXVECTOR2 GetPlayerPos() const
	{
		return m_PlayerPos;
	}

	inline void SetEnemyPos(D3DXVECTOR2* _enemyPos)
	{
		m_EnemyPos = *_enemyPos;
	}

	D3DXVECTOR2 GetEnemyPos() const
	{
		return m_EnemyPos;
	}

private:
	CombatManager();
	~CombatManager();

	D3DXVECTOR2 m_PlayerPos;
	D3DXVECTOR2 m_EnemyPos;
	
};


#endif
