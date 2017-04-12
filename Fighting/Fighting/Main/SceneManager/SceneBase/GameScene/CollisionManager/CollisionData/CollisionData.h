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
	friend CollisionManager;
public:
	enum COLLISION_TYPE
	{
		WALL,   //!< 壁の判定
		BODY,	//!< 体の判定
		ATTACK  //!< 攻撃の判定
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
		CollisionState(const D3DXVECTOR2* _pos,const D3DXVECTOR2* _collisionRect,const COLLISION_TYPE _collisionType)
		{
			Pos = *_pos;
			CollisionRect = *_collisionRect;
			CollisionType = _collisionType;
			HitType = NON_HIT;
		}
		D3DXVECTOR2	   Pos;
		D3DXVECTOR2    CollisionRect;
		COLLISION_TYPE CollisionType;
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
	 * 判定座標の更新
	 */
	void Update(const CollisionState* _collisionState);

	/**
	 * 
	 */
	inline CollisionState GetCollisionState() const
	{
		return m_CollisionState;
	}

private:
	CollisionState m_CollisionState;

};


#endif
