/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"
#include "Texture/TextureManager.h"
#include "Dx11/DX11Manager.h"
#include "Window/Window.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "CommandManager\CommandManager.h"
#include "../../../../CollisionManager/CollisionManager.h"
#include "../../../../CombatManager/CombatManager.h"
#include "../Bullet/Bullet.h"

const D3DXVECTOR2 Player::m_HPBarPos = D3DXVECTOR2(HPBar::m_HPBarRect.x / 2 + 70, 67.5);


Player::Player() :
CharacterBase(D3DXVECTOR2(220, 550), D3DXVECTOR2(256, 256), true),
m_pCommandManager(std::unique_ptr<CommandManager>(new CommandManager())),
m_MoveSpeed(4.5f)
{
	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/Character.png", &m_TextureIndex);
	// Lib::TextureManager Texture Load end

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

	SINGLETON_INSTANCE(CombatManager).SetPlayerHP(m_CharacterState.HP);
	SINGLETON_INSTANCE(CombatManager).SetPlayerPos(&m_Pos);
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
	if (m_CharacterState.HP <= 0 && m_isAnimEnd) return;

	KeyCheck();

	/* 操作がされないとステートが変化しないので、最初に */
	if (!m_CharacterState.IsAttackMotion)
	{
		m_AnimState = ANIM_WAIT;
		m_AnimOperation = Lib::ANIM_LOOP;
	}

	if (!m_CharacterState.IsDamageMotion)
	{
		if (!m_CharacterState.IsJump)
		{
			LeftMoveControl();
			RightMoveControl();
			UpMoveControl();
			DownMoveControl();
		}

		ZKeyControl();
		XKeyControl();
		CKeyControl();
		VKeyControl();
		CommandControl();
	}

	/* ジャンプしているかチェック */
	if (m_CharacterState.IsJump)
	{
		JumpControl();
	}

	CollisionControl();

	/* テストコード */
	if (m_pCommandManager->Update() == CommandManager::HADOUKEN)
	{
		m_AnimState = ANIM_SHOT;
		m_AnimOperation = Lib::ANIM_NORMAL;
		m_CharacterState.IsAttackMotion = true;
	}

	/* 攻撃のモーション中か */
	if (m_CharacterState.IsAttackMotion)
	{
		AttackControl();
		m_isAnimEnd = m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
		int animNum = m_pAnimUvController[m_AnimState]->GetAnimNum();
		int animCount = m_pAnimUvController[m_AnimState]->GetAnimCount();

		if (m_AnimState == ANIM_SHOT && animCount > animNum - 4)
		{
			m_pBullet->InitState(&m_Pos, m_CharacterState.IsRight);
		}
	}
	else if (m_CharacterState.IsDamageMotion)
	{
		m_isAnimEnd = m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
	}
	else
	{
		m_pAnimUvController[m_AnimState]->Control(false, m_AnimOperation);
	}

	m_pBullet->Update();
	D3DXVECTOR2 enemyPos = SINGLETON_INSTANCE(CombatManager).GetEnemyPos();
	m_CharacterState.IsRight = (m_Pos.x < enemyPos.x);
	SINGLETON_INSTANCE(CombatManager).SetPlayerPos(&m_Pos);
	SINGLETON_INSTANCE(CombatManager).SetPlayerHP(m_CharacterState.HP);
	m_OldPos = m_Pos;
}

void Player::Draw()
{
	/* 相手が右に居れば右に向き、左に居れば左を向かせる */
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
	m_pBullet->Draw();
#ifdef _DEBUG
	CollisionDraw();
#endif
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::KeyCheck()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_LEFT);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RIGHT);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_UPARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_DOWNARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_Z); // 弱パンチボタン.
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_X); // 強パンチボタン.
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_C); // 弱キックボタン.
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_V); // 強キックボタン.
}

void Player::LeftMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_ON &&
		!m_CharacterState.IsSquat &&
		!m_CharacterState.IsAttackMotion)
	{
		if (!m_CharacterState.IsJump)
		{
			if (m_CharacterState.IsRight)
			{
				m_AnimState = ANIM_BACK_WALK;
			}
			else
			{
				m_AnimState = ANIM_FRONT_WALK;
			}
			m_AnimOperation = Lib::ANIM_LOOP;
		}
		m_Pos.x -= m_MoveSpeed;
	}
}

void Player::RightMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHT] == Lib::KEY_ON &&
		!m_CharacterState.IsSquat &&
		!m_CharacterState.IsAttackMotion)
	{
		if (!m_CharacterState.IsJump)
		{
			if (m_CharacterState.IsRight)
			{
				m_AnimState = ANIM_FRONT_WALK;
			}
			else
			{
				m_AnimState = ANIM_BACK_WALK;
			}
			m_AnimOperation = Lib::ANIM_LOOP;
		}
		m_Pos.x += m_MoveSpeed;
	}
}

void Player::UpMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_UPARROW] == Lib::KEY_PUSH &&
		!m_CharacterState.IsJump &&
		!m_CharacterState.IsAttackMotion)
	{
		/* ジャンプ処理 */
		m_OldHeight = m_Pos.y;
		m_Pos.y -= m_JumpPower;
		m_CharacterState.IsJump = true;
		if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHTARROW] == Lib::KEY_ON)
		{ 
			m_JumpWidth += m_MoveSpeed;
		}
		else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFTARROW] == Lib::KEY_ON)
		{
			m_JumpWidth -= m_MoveSpeed;
		}
	}
}

void Player::DownMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON &&
		!m_CharacterState.IsJump &&
		!m_CharacterState.IsAttackMotion)
	{
		m_AnimState = ANIM_SQUAT;
		m_AnimOperation = Lib::ANIM_NORMAL;
		m_CharacterState.IsSquat = true;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_RELEASE)
	{
		m_pAnimUvController[ANIM_SQUAT]->ResetAnim();
		m_CharacterState.IsSquat = false;
	}
}

void Player::ZKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_PUSH)
	{
		if (!m_CharacterState.IsAttackMotion)
		{
			if (m_CharacterState.IsSquat && !m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_SQUAT_LOW_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else if (!m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_LOW_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
		}
	}
}

void Player::XKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_X] == Lib::KEY_PUSH)
	{
		if (!m_CharacterState.IsAttackMotion)
		{
			if (m_CharacterState.IsSquat && !m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_SQUAT_HIGH_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else if (!m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_HIGH_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
		}
	}
}

void Player::CKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_C] == Lib::KEY_PUSH)
	{
		if (!m_CharacterState.IsAttackMotion)
		{
			if (m_CharacterState.IsSquat && !m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_SQUAT_LOW_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else if (!m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_LOW_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
		}
	}
}

void Player::VKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_V] == Lib::KEY_PUSH)
	{
		if (!m_CharacterState.IsAttackMotion)
		{
			if (m_CharacterState.IsSquat && !m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_SQUAT_HIGH_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else if (!m_CharacterState.IsJump)
			{
				m_AnimState = ANIM_HIGH_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
		}
	}
}

void Player::CommandControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHT] == Lib::KEY_ON)
	{
		if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON)
		{
			if (m_CharacterState.IsRight)
			{
				m_pCommandManager->PushButton(CommandManager::KEY_RIGHT_SLANT);
			}
			else
			{
				m_pCommandManager->PushButton(CommandManager::KEY_LEFT_SLANT);
			}
		}
		else
		{
			if (m_CharacterState.IsRight)
			{
				m_pCommandManager->PushButton(CommandManager::KEY_RIGHT);
			}
			else
			{
				m_pCommandManager->PushButton(CommandManager::KEY_LEFT);
			}
		}
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_ON)
	{
		if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON)
		{
			if (m_CharacterState.IsRight)
			{
				m_pCommandManager->PushButton(CommandManager::KEY_LEFT_SLANT);
			}
			else
			{
				m_pCommandManager->PushButton(CommandManager::KEY_RIGHT_SLANT);
			}
		}
		else
		{
			if (m_CharacterState.IsRight)
			{
				m_pCommandManager->PushButton(CommandManager::KEY_LEFT);
			}
			else
			{
				m_pCommandManager->PushButton(CommandManager::KEY_RIGHT);
			}
		}
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON)
	{
		m_pCommandManager->PushButton(CommandManager::KEY_DOWN);
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_ON)
	{
		m_pCommandManager->PushButton(CommandManager::KEY_LOW_PUNCH);
	}
}
