/**
 * @file   CollisionData.cpp
 * @brief  CollisionDataクラスの実装
 * @author kotani
 */
#include "CollisionData.h"


CollisionData::CollisionData(const CollisionState* _collisionState) :
m_CollisionState(*_collisionState)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool CollisionData::HitCheck(const CollisionState* _collisionState)
{
	CollisionState v1 = m_CollisionState;
	CollisionState v2 = *_collisionState;

	m_CollisionState.ReceiveDamage = 0;
	m_CollisionState.HitType = NON_HIT;

	if ((v1.Pos.x - v1.CollisionRect.x / 2) <= (v2.Pos.x + v2.CollisionRect.x / 2) &&
		(v1.Pos.x + v1.CollisionRect.x / 2) >= (v2.Pos.x - v2.CollisionRect.x / 2) &&
		(v1.Pos.y - v1.CollisionRect.y / 2) <= (v2.Pos.y + v2.CollisionRect.y / 2) &&
		(v1.Pos.y + v1.CollisionRect.y / 2) >= (v2.Pos.y - v2.CollisionRect.y / 2))
	{
		if (m_CollisionState.CollisionType == BODY &&
			_collisionState->CollisionType == ATTACK)
		{
			m_CollisionState.HitType = ATTACK_HIT;
			m_CollisionState.ReceiveDamage = v2.GiveDamage;
			return true;
		}
		else if ((m_CollisionState.CollisionType == BODY || m_CollisionState.CollisionType == ATTACK) &&
			(_collisionState->CollisionType == BODY || _collisionState->CollisionType == WALL))
		{
			m_CollisionState.HitType = BODY_HIT;
			return true;
		}
	}
	return false;
}
