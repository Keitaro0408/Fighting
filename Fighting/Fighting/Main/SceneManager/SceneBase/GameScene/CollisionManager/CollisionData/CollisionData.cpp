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

void CollisionData::Update(const CollisionState* _collisionState)
{
	m_CollisionState = *_collisionState;
}
