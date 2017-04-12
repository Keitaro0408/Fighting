/**
 * @file   Enemy.cpp
 * @brief  Enemyクラスの実装
 * @author kotani
 */
#include "Enemy.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "KeyDevice.h"
#include "../../CombatManager/CombatManager.h"
#include "../../../../CollisionManager/CollisionManager.h"

const D3DXVECTOR2 Enemy::m_HPBarPos = D3DXVECTOR2(1280 - (HPBar::m_HPBarRect.x / 2 + 70), 67.5);


Enemy::Enemy(const std::shared_ptr<CombatManager> &_pCombatManager) :
CharacterBase(D3DXVECTOR2(1060, 550), D3DXVECTOR2(256, 256), _pCombatManager, false),
m_MoveSpeed(4.5f)
{
	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/GameScene/Enemy.png", &m_TextureIndex);
	// Lib::TextureManager Texture Load End

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));
	m_pVertex->Init(&m_RectSize, m_pAnimTexture[ANIM_WAIT]->GetUV());
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end

	m_pCollisionData.reset(new CollisionData(&CollisionData::CollisionState(&m_Pos, &m_StandRectCollision, CollisionData::BODY)));
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData.get());

	m_pHPBar.reset(new HPBar(&m_HPBarPos));

	m_pCombatManager->SetEnemyPos(&m_Pos);
}

Enemy::~Enemy()
{
	m_pVertex->Release();
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Enemy::Update()
{
	m_AnimState = ANIM_WAIT;

	m_pCombatManager->SetEnemyPos(&m_Pos);
	
	SINGLETON_INSTANCE(CollisionManager).Update();
	CollisionControl();
	m_isAnimEnd = m_pAnimTexture[m_AnimState]->Control(false, m_AnimOperation);

	m_OldPos = m_Pos;
}

void Enemy::Draw()
{
	// 相手が右に居れば右に向き、左に居れば左を向かせる
	D3DXVECTOR2 playerPos = m_pCombatManager->GetPlayerPos();
	m_CharacterState.IsRight = (m_Pos.x < playerPos.x);
	if (m_CharacterState.IsRight)
	{
		m_pVertex->Draw(&m_Pos, m_pAnimTexture[m_AnimState]->GetUV());
	}
	else
	{
		D3DXVECTOR2 UV[4];
		memcpy(UV, m_pAnimTexture[m_AnimState]->GetUV(), sizeof(D3DXVECTOR2) * 4);
		InvertUV(UV);
		m_pVertex->Draw(&m_Pos, UV);
	}
	m_pHPBar->Draw();
#ifdef _DEBUG
	CollisionDraw();
#endif
}
