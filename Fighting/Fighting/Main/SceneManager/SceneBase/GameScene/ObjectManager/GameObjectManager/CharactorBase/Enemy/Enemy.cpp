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
	m_pCombatManager->SetEnemyPos(&m_Pos);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	m_pAnimTexture[m_AnimState]->Control(false, Lib::ANIM_LOOP);
	m_pCombatManager->SetEnemyPos(&m_Pos);
}

void Enemy::Draw()
{
	// 相手が右に居れば右に向き、左に居れば左を向かせる
	D3DXVECTOR2 playerPos = m_pCombatManager->GetPlayerPos();
	m_Pos.x < playerPos.x ? (m_CharacterState.isRight = true) : (m_CharacterState.isRight = false);

	if (m_CharacterState.isRight)
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
#ifdef _DEBUG
	CollisionDraw();
#endif
}