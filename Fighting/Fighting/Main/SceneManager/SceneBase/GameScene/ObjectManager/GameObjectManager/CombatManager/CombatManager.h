/**
 * @file   CombatManager.h
 * @brief  CombatManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H
#include <D3DX10.h>

/**
 * 戦闘を管理するクラス
 */
class CombatManager
{
public:
	CombatManager() = default;
	~CombatManager() = default;

	enum RESULT
	{
		RESULT_WIN,     //!< 勝ち
		RESULT_LOSE,	//!< 負け
		RESULT_DRAW,	//!< 引き分け
		IN_COMBAT		//!< 戦闘中
	};

	/**
	 * 勝敗の判定
	 * @return 判定結果
	 */
	RESULT BattleJudge();

	/**
	 * プレイヤーの座標のセット
	 * @param[in] _playerPos プレイヤーの座標
	 */
	inline void SetPlayerPos(D3DXVECTOR2* _playerPos)
	{
		m_PlayerPos = *_playerPos;
	}
	/**
	 * プレイヤーの座標の取得
	 */
	inline D3DXVECTOR2 GetPlayerPos() const
	{
		return m_PlayerPos;
	}

	/**
	 * 敵の座標のセット
	 * @param[in] _enemyPos 敵の座標
	 */
	inline void SetEnemyPos(D3DXVECTOR2* _enemyPos)
	{
		m_EnemyPos = *_enemyPos;
	}

	/**
	 * 敵の座標の取得
	 */
	inline D3DXVECTOR2 GetEnemyPos() const
	{
		return m_EnemyPos;
	}

private:
	D3DXVECTOR2 m_PlayerPos;
	D3DXVECTOR2 m_EnemyPos;
	
};


#endif
