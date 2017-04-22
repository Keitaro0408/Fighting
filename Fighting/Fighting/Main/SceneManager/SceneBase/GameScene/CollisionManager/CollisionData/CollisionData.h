/**
 * @file   CollisionData.h
 * @brief  CollisionDataクラスのヘッダファイル
 * @author kotani
 */
#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H
#include <D3DX10.h>

class CollisionManager;

class CollisionData
{
public:
	enum COLLISION_TYPE
	{
		WALL,   //!< 壁の判定
		BODY,	//!< 体の判定
		ATTACK, //!< 攻撃の判定
		COLLISION_NONE
	};

	enum HIT_TYPE
	{
		NON_HIT,   //!< 当たっていない
		BODY_HIT,  //!< 体に当たった
		ATTACK_HIT //!< 攻撃に当たった
	};

	struct CollisionState
	{
		CollisionState();
		CollisionState(const D3DXVECTOR2* _pos,const D3DXVECTOR2* _collisionRect,const COLLISION_TYPE _collisionType, int _giveDamage)
		{
			Pos = *_pos;
			CollisionRect = *_collisionRect;
			CollisionType = _collisionType;
			GiveDamage = _giveDamage;
			HitType = NON_HIT;
		}
		D3DXVECTOR2	   Pos;
		D3DXVECTOR2    CollisionRect;
		COLLISION_TYPE CollisionType;
		int			   GiveDamage;
		int			   ReceiveDamage;
		HIT_TYPE	   HitType;
	};

	/**
	 * コンストラクタ
	 * @param[in]
	 */
	CollisionData(const CollisionState* _collisionState);
	
	/**
	 * デストラクタ
	 */
	~CollisionData() = default;

	/**
	 * 判定チェック
	 * @param[in] _collisionState チェックする判定
	 * @return 当たったらtrue
	 */
	bool HitCheck(const CollisionState* _collisionState);

	/**
	 * 当たり判定の設定
	 * @param[in] _collisionState 更新した判定
	 */
	inline void SetCollisionState(const CollisionState* _collisionState)
	{
		m_CollisionState = *_collisionState;
	}

	/**
	 * 当たり判定の取得
	 */
	inline CollisionState GetCollisionState() const
	{
		return m_CollisionState;
	}

	inline void SetIndex(int _index)
	{
		m_Index = _index;
	}

	inline int GetIndex()
	{
		return m_Index;
	}

private:
	CollisionState m_CollisionState;
	int			   m_Index; //!< 何番目の配列にセットされたか?

};


#endif
