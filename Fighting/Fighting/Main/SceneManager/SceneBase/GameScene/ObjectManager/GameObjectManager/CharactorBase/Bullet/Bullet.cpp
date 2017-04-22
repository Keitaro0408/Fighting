/**
 * @file   Bullet.cpp
 * @brief  Bulletクラスの実装
 * @author kotani
 */
#include "Bullet.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "../../../../CollisionManager/CollisionManager.h"


Bullet::Bullet() :
m_IsEnable(false),
m_RectCollision(D3DXVECTOR2(60, 60))
{
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/effect.png", &m_TextureIndex);
	m_pAnimTexture = (std::unique_ptr<Lib::AnimTexture>(new Lib::AnimTexture()));
	m_pAnimTexture->LoadAnimation("Resource/Texture/GameScene/Effect.anim", "Shot");
	m_pAnimTexture->SetAnimFrame(4);

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));
	m_pVertex->Init(&D3DXVECTOR2(100, 100), m_pAnimTexture->GetUV());
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end

	m_pCollisionData.reset(new CollisionData(&CollisionData::CollisionState(&m_Pos, &m_RectCollision, CollisionData::COLLISION_NONE, 10)));
	SINGLETON_INSTANCE(CollisionManager).AddCollision(m_pCollisionData.get());

}

Bullet::~Bullet()
{
	m_pVertex->Release();
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Bullet::InitState(D3DXVECTOR2* _pos, bool _isRight)
{
	m_Pos = *_pos;
	m_IsRight = _isRight;
	m_IsEnable = true;

	m_IsRight ? (m_Pos.x += 70) : (m_Pos.x -= 70);
}

void Bullet::Update()
{
	if (!m_IsEnable) return;
	m_IsRight ? m_Pos.x += 5 : m_Pos.x -= 5;
	CollisionControl();
	m_pAnimTexture->Control(false,Lib::ANIM_LOOP);
}

void Bullet::Draw()
{
	if (!m_IsEnable) return;

	if (m_IsRight)
	{
		m_pVertex->Draw(&m_Pos, m_pAnimTexture->GetUV());
	}
	else
	{
		D3DXVECTOR2 UV[4];
		memcpy(UV, m_pAnimTexture->GetUV(), sizeof(D3DXVECTOR2) * 4);
		InvertUV(UV);
		m_pVertex->Draw(&m_Pos, UV);
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Bullet::CollisionControl()
{
	CollisionData::HIT_TYPE hitType = m_pCollisionData->GetCollisionState().HitType;
	m_pCollisionData->SetCollisionState(&CollisionData::CollisionState(&m_Pos, &m_RectCollision, CollisionData::ATTACK, 10));
	if (hitType == CollisionData::BODY_HIT)
	{
		m_IsEnable = false;
		m_pCollisionData->SetCollisionState(&CollisionData::CollisionState(&m_Pos, &m_RectCollision, CollisionData::COLLISION_NONE, 10));
	}
	else if (hitType != CollisionData::NON_HIT)
	{
		int var = 0;
	}

	SINGLETON_INSTANCE(CollisionManager).Update(m_pCollisionData->GetIndex());
}

void Bullet::InvertUV(D3DXVECTOR2* _uv)
{
	D3DXVECTOR2 tmpUV[4];

	for (int i = 0; i < 4; i++)
	{
		tmpUV[i] = _uv[i];
	}

	_uv[0] = tmpUV[1];
	_uv[1] = tmpUV[0];
	_uv[2] = tmpUV[3];
	_uv[3] = tmpUV[2];
}
