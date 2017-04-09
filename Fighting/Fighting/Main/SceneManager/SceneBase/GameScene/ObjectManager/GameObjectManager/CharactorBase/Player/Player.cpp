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
#include "../../CombatManager/CombatManager.h"
#include "CommandManager\CommandManager.h"


Player::Player(const std::shared_ptr<CombatManager> &_pCombatManager) :
CharacterBase(D3DXVECTOR2(220, 550), D3DXVECTOR2(256, 256), _pCombatManager, true),
m_pCommandManager(std::unique_ptr<CommandManager>(new CommandManager())),
m_MoveSpeed(4.5f)
{
	// Lib::TextureManager Texture Load
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/GameScene/Character.png", &m_TextureIndex);

	// Lib::TextureManager Texture Load end

	// Lib::Vertex2D Init
	m_pVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pVertex->Init(&m_RectSize, m_pAnimTexture[ANIM_WAIT]->GetUV());

	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_TextureIndex));
	// Lib::Vertex2D Init end

	m_pCombatManager->SetPlayerPos(&m_Pos);
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
	KeyCheck();

	/* 操作がされないとステートが変化しないので、最初に */
	if (!m_CharacterState.IsAttackMotion)
	{
		m_AnimState = ANIM_WAIT;
		m_AnimOperation = Lib::ANIM_LOOP;
	}

	/* ジャンプしているかチェック */
	if (m_CharacterState.IsJump)
	{
		JumpControl();
	}

	LeftMoveControl();
	RightMoveControl();
	UpMoveControl();
	DownMoveControl();

	ZKeyControl();
	XKeyControl();
	CKeyControl();
	VKeyControl();
	
	/* 攻撃のモーション中か */
	if (m_CharacterState.IsAttackMotion)
	{
		m_AnimOperation = Lib::ANIM_NORMAL;
		bool isAnimEnd = m_pAnimTexture[m_AnimState]->Control(false, m_AnimOperation);
		/* アニメーション再生が最後ならフラグを反転させてIsAttackMotionをfalseにしている */
		m_CharacterState.IsAttackMotion = !isAnimEnd;
		if (m_CharacterState.IsAttackMotion)
		{
			int attackAnimCount = m_pAnimTexture[m_AnimState]->GetAnimCount();
			
			if (m_SkillSpec[m_AnimState].FirstHitCheckCount < attackAnimCount)
			{

			}
		}
		else
		{
			m_pAnimTexture[m_AnimState]->ResetAnim();
		}
	}
	else
	{
		m_pAnimTexture[m_AnimState]->Control(false, m_AnimOperation);
	}
	
	m_pCombatManager->SetPlayerPos(&m_Pos);
}

void Player::Draw()
{
	// 相手が右に居れば右に向き、左に居れば左を向かせる
	D3DXVECTOR2 enemyPos = m_pCombatManager->GetEnemyPos();
	m_CharacterState.IsRight = (m_Pos.x < enemyPos.x);
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
		m_CharacterState.IsJump = false;
		m_Pos.y = 550.f;
	}
}

void Player::LeftMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFT] == Lib::KEY_ON && 
		!m_CharacterState.IsSquat &&
		!m_CharacterState.IsAttackMotion)
	{
		if (!m_CharacterState.IsJump)
		{
			m_AnimState = ANIM_BACK_WALK;
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
			m_AnimState = ANIM_FRONT_WALK;
			m_AnimOperation = Lib::ANIM_LOOP;
		}
		m_Pos.x += m_MoveSpeed;
	}
}

void Player::UpMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_UPARROW] == Lib::KEY_PUSH &&
		!m_CharacterState.IsJump &&
		!m_CharacterState.IsSquat &&
		!m_CharacterState.IsAttackMotion)
	{
		// ジャンプ処理.
		m_OldHeight = m_Pos.y;
		m_Pos.y -= m_JumpPower;
		m_CharacterState.IsJump = true;
	}
}

void Player::DownMoveControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_ON && 
		!m_CharacterState.IsJump &&
		!m_CharacterState.IsAttackMotion)
	{
		m_CharacterState.IsSquat = true;
		m_AnimState = ANIM_SQUAT;
		m_AnimOperation = Lib::ANIM_NORMAL;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_DOWNARROW] == Lib::KEY_RELEASE)
	{
		m_CharacterState.IsSquat = false;
		m_pAnimTexture[ANIM_SQUAT]->ResetAnim();
	}
}

void Player::ZKeyControl()
{
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_Z] == Lib::KEY_PUSH)
	{
		if (!m_CharacterState.IsAttackMotion)
		{
			if (m_CharacterState.IsSquat)
			{
				m_AnimState = ANIM_SQUAT_LOW_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else
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
			if (m_CharacterState.IsSquat)
			{
				m_AnimState = ANIM_SQUAT_HIGH_PUNCH;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else
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
			if (m_CharacterState.IsSquat)
			{
				m_AnimState = ANIM_SQUAT_LOW_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else
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
			if (m_CharacterState.IsSquat)
			{
				m_AnimState = ANIM_SQUAT_HIGH_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
			else
			{
				m_AnimState = ANIM_HIGH_KICK;
				m_AnimOperation = Lib::ANIM_NORMAL;
				m_CharacterState.IsAttackMotion = true;
			}
		}
	}
}
