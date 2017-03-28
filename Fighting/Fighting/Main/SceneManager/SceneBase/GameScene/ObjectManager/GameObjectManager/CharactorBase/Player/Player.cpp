/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "KeyDevice.h"

Player::Player() :
CharacterBase(D3DXVECTOR2(120, 550), D3DXVECTOR2(256, 256), true),
m_PlayerAnimState(WAIT),
m_MoveSpeed(3.f)
{
	// Lib::AnimTexture Init
	InitAnim(WAIT, "Wait", 7);
	InitAnim(FRONT_WALK, "FrontWalk", 7);
	InitAnim(BACK_WALK, "BackWalk", 7);
	// Lib::AnimTexture Init End

	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/GameScene/Character.png", &m_TextureIndex);
	// Lib::TextureManager Texture Load End

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pVertex->Init(&m_RectSize, m_pAnimTexture[WAIT]->GetUV());
	
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end
}

Player::~Player()
{
	m_pVertex->Release();

	SINGLETON_INSTANCE(Lib::TextureManager).
		ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_LEFT);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RIGHT);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_UPARROW);

	m_pAnimTexture[m_PlayerAnimState]->Control(true);

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_ON)
	{
		m_PlayerAnimState = BACK_WALK;
		m_Pos.x -= m_MoveSpeed;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHT] == Lib::KEY_ON)
	{
		m_PlayerAnimState = FRONT_WALK;
		m_Pos.x += m_MoveSpeed;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_UPARROW] == Lib::KEY_ON)
	{
		// ジャンプ処理.
	}
	else
	{
		m_PlayerAnimState = WAIT;
	}
}

void Player::Draw()
{
	m_pVertex->Draw(&m_Pos, m_pAnimTexture[m_PlayerAnimState]->GetUV());
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame)
{
	m_pAnimTexture[_animEnum] = (std::unique_ptr<Lib::AnimTexture>(new Lib::AnimTexture()));
	m_pAnimTexture[_animEnum]->LoadAnimation("Resource/GameScene/Character.anim", _animName);
	m_pAnimTexture[_animEnum]->SetAnimFrame(_setFrame);
}
