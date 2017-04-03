#include "Enemy.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "KeyDevice.h"


Enemy::Enemy() :
CharacterBase(D3DXVECTOR2(1060, 550), D3DXVECTOR2(256, 256), false),
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
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	m_pAnimTexture[m_AnimState]->Control(false, Lib::ANIM_LOOP);
}

void Enemy::Draw()
{
	D3DXVECTOR2 UV[4];
	memcpy(UV, m_pAnimTexture[m_AnimState]->GetUV(), sizeof(D3DXVECTOR2) * 4);
	InvertUV(UV);
	m_pVertex->Draw(&m_Pos, UV);
}