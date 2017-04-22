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
	m_pCollisionData[m_pCollisionData.size() - 1]->SetIndex(m_pCollisionData.size() - 1);
}

void CollisionManager::Update(int _index)
{
	if (m_pCollisionData.size() < 1) return;

	for (unsigned int j = 0; j < m_pCollisionData.size(); j++)
	{
		if (_index != j)
		{
			if (m_pCollisionData[_index]->HitCheck(&m_pCollisionData[j]->GetCollisionState()))
			{
				break;
			}
		}
	}
}
