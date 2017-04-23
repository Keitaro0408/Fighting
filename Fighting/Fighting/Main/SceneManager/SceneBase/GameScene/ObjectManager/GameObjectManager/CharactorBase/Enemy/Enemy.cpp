﻿/**
 * @file   Enemy.cpp
 * @brief  Enemyクラスの実装
 * @author kotani
 */
#include "Enemy.h"
#include "Texture/TextureManager.h"
#include "Dx11/DX11Manager.h"
#include "Window/Window.h"
#include "DxInput/KeyBoard/KeyDevice.h"
#include "../../../../CollisionManager/CollisionManager.h"
#include "../../../../CombatManager/CombatManager.h"

const D3DXVECTOR2 Enemy::m_HPBarPos = D3DXVECTOR2(1280 - (HPBar::m_HPBarRect.x / 2 + 70), 67.5);


Enemy::Enemy() :
CharacterBase(D3DXVECTOR2(1060, 550), D3DXVECTOR2(256, 256), false),
m_MoveSpeed(4.5f)
{
	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/Enemy.png", &m_TextureIndex);
	// Lib::TextureManager Texture Load End

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));
	m_pVertex->Init(&m_RectSize, m_pAnimUvController[ANIM_WAIT]->GetUV());
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end

	m_pCollisionData.reset(new CollisionData(&CollisionData::CollisionState(&m_Pos, &m_StandRectCollision, CollisionData::BODY,0)));
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData.get());

	m_pHPBar.reset(new HPBar(&m_HPBarPos));

	SINGLETON_INSTANCE(CombatManager).SetEnemyHP(m_CharacterState.HP);
	SINGLETON_INSTANCE(CombatManager).SetEnemyPos(&m_Pos);
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
	if (!m_CharacterState.IsAttackMotion && m_CharacterState.HP != 0)
	{
		m_AnimState = ANIM_WAIT;
		m_AnimOperation = Lib::ANIM_LOOP;
	}

	D3DXVECTOR2 playerPos = SINGLETON_INSTANCE(CombatManager).GetPlayerPos();
	if (abs(m_Pos.x - playerPos.x) > 400.f)
	{
		if (m_CharacterState.IsRight)
		{
			m_AnimState = ANIM_FRONT_WALK;
			m_Pos.x += m_MoveSpeed;
		}
		else
		{
			m_AnimState = ANIM_FRONT_WALK;
			m_Pos.x -= m_MoveSpeed;
		}
	}

	CollisionControl();
	
	/* 攻撃のモーション中か */
	if (m_CharacterState.IsAttackMotion)
	{
		AttackControl();
		m_isAnimEnd = m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
	}
	else if (m_CharacterState.IsDamageMotion)
	{
		m_isAnimEnd = m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
	}
	else
	{
		m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
	}

	m_CharacterState.IsRight = (m_Pos.x < playerPos.x);
	SINGLETON_INSTANCE(CombatManager).SetEnemyPos(&m_Pos);
	SINGLETON_INSTANCE(CombatManager).SetEnemyHP(m_CharacterState.HP);
	m_OldPos = m_Pos;
}

void Enemy::Draw()
{
	// 相手が右に居れば右に向き、左に居れば左を向かせる
	if (m_CharacterState.IsRight)
	{
		m_pVertex->Draw(&m_Pos, m_pAnimUvController[m_AnimState]->GetUV());
	}
	else
	{
		D3DXVECTOR2 UV[4];
		memcpy(UV, m_pAnimUvController[m_AnimState]->GetUV(), sizeof(D3DXVECTOR2) * 4);
		InvertUV(UV);
		m_pVertex->Draw(&m_Pos, UV);
	}
	m_pHPBar->Draw(m_CharacterState.HP);
#ifdef _DEBUG
	CollisionDraw();
#endif
}
