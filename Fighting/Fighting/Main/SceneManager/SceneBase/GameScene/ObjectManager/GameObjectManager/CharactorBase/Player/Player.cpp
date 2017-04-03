﻿/**
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
CharacterBase(D3DXVECTOR2(220, 550), D3DXVECTOR2(256, 256), true),
m_MoveSpeed(4.5f)
{
	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/GameScene/Character.png", &m_TextureIndex);
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
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_DOWNARROW);

	/* ジャンプしているかチェック */
	if (m_isJump)
	{
		JumpControl();
	}
	else if (m_AnimState != ANIM_SQUAT)
	{
		m_AnimOperation =  Lib::ANIM_LOOP;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHT] == Lib::KEY_OFF &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_OFF &&
		SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWN] == Lib::KEY_OFF &&
		!m_isJump)
	{
		m_AnimState = ANIM_WAIT;
		m_AnimOperation = Lib::ANIM_LOOP;
	}

	LeftKeyControl();
	RightKeyControl();
	UpKeyControl();
	DownKeyControl();

	if (m_AnimState == ANIM_SQUAT && m_AnimOperation == Lib::ANIM_LOOP)
	{
		int test = 0;
		test++;
	}
	m_pAnimTexture[m_AnimState]->Control(false, m_AnimOperation);
}

void Player::Draw()
{
	if (m_AnimState == ANIM_SQUAT && m_AnimOperation == Lib::ANIM_LOOP)
	{
		int test = 0;
		test++;
	}
	m_pVertex->Draw(&m_Pos, m_pAnimTexture[m_AnimState]->GetUV());
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::JumpControl()
{
	m_AnimState = ANIM_JUMP;
	m_AnimOperation = Lib::ANIM_NORMAL;

	float HeightTmp = m_Pos.y;
	m_Pos.y += (m_Pos.y - m_OldHeight) + 1.f;
	m_OldHeight = HeightTmp;
	if (550.f < m_Pos.y)
	{
		m_pAnimTexture[ANIM_JUMP]->ResetAnim();
		m_isJump = false;
		m_Pos.y = 550.f;
	}
}

void Player::LeftKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_ON)
	{
		if (!m_isJump)
		{
			m_AnimState = ANIM_BACK_WALK;
			m_AnimOperation = Lib::ANIM_LOOP;
		}
		m_Pos.x -= m_MoveSpeed;
	}
}

void Player::RightKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHT] == Lib::KEY_ON)
	{
		if (!m_isJump)
		{
			m_AnimState = ANIM_FRONT_WALK;
			m_AnimOperation = Lib::ANIM_LOOP;
		}
		m_Pos.x += m_MoveSpeed;
	}
}

void Player::UpKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_UPARROW] == Lib::KEY_PUSH &&
		!m_isJump)
	{
		// ジャンプ処理.
		m_OldHeight = m_Pos.y;
		m_Pos.y -= m_JumpPower;
		m_isJump = true;
	}
}

void Player::DownKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON && !m_isJump)
	{
		m_isSquat = true;
		m_AnimState = ANIM_SQUAT;
		m_AnimOperation = Lib::ANIM_NORMAL;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_RELEASE)
	{
		m_isSquat = false;
		m_pAnimTexture[ANIM_SQUAT]->ResetAnim();
	}
}
