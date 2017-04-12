/**
 * @file   CollisionManager.cpp
 * @brief  CollisionManagerクラスの実装
 * @author kotani
 */
#include "CollisionManager.h"
#include "CollisionData\CollisionData.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void CollisionManager::AddCollision(CollisionData* _pCollisionData)
{
	m_pCollisionData.push_back(_pCollisionData);
}

void CollisionManager::Update()
{
	if (m_pCollisionData.size() < 1) return;

	for (unsigned int i = 0; i < m_pCollisionData.size(); i++)
	{
		CollisionData::CollisionState v1 = m_pCollisionData[i]->GetCollisionState();
		for (unsigned int j = 0; j < m_pCollisionData.size(); j++)
		{
			CollisionData::CollisionState v2 = m_pCollisionData[j]->GetCollisionState();
			if (i != j &&
				(v1.Pos.x - v1.CollisionRect.x / 2) <= (v2.Pos.x + v2.CollisionRect.x / 2) && 
				(v1.Pos.x + v1.CollisionRect.x / 2) >= (v2.Pos.x - v2.CollisionRect.x / 2) && 
				(v1.Pos.y - v1.CollisionRect.y / 2) <= (v2.Pos.y + v2.CollisionRect.y / 2) && 
				(v1.Pos.y + v1.CollisionRect.y / 2) >= (v2.Pos.y - v2.CollisionRect.y / 2))
			{
				/* 当たった処理 */
				HitControl(i,j);
			}
			else if (i != j)
			{
				m_pCollisionData[i]->m_CollisionState.HitType = CollisionData::NON_HIT;
			}

		}
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void CollisionManager::HitControl(int _countI, int _countJ)
{
	if (m_pCollisionData[_countI]->m_CollisionState.CollisionType == CollisionData::BODY &&
		m_pCollisionData[_countJ]->m_CollisionState.CollisionType == CollisionData::ATTACK)
	{
		m_pCollisionData[_countI]->m_CollisionState.HitType = CollisionData::ATTACK_HIT;
	}
	else if (m_pCollisionData[_countI]->m_CollisionState.CollisionType == CollisionData::BODY &&
		m_pCollisionData[_countJ]->m_CollisionState.CollisionType == CollisionData::BODY ||
		m_pCollisionData[_countJ]->m_CollisionState.CollisionType == CollisionData::WALL)
	{
		m_pCollisionData[_countI]->m_CollisionState.HitType = CollisionData::BODY_HIT;
	}
}
