﻿/**
 * @file   CharacterBase.cpp
 * @brief  CharacterBaseクラスの実装
 * @author kotani
 */
#include "CharacterBase.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "DSoundManager.h"
#include "Bullet\Bullet.h"
#include "../../../CollisionManager/CollisionManager.h"

const float CharacterBase::m_GroundHeight = 550;
const float CharacterBase::m_StageWidth = 1280.f;
const float CharacterBase::m_JumpPower = 23.f;


CharacterBase::CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, bool isRight) :
m_Pos(_pos),
m_RectSize(_rectSize),
m_AnimState(ANIM_WAIT),
m_isAnimEnd(false),
m_StandRectCollision(D3DXVECTOR2(60, 200)),
m_SquatRectCollision(D3DXVECTOR2(80, 100)),
m_pBullet(std::unique_ptr<Bullet>(new Bullet()))
{
	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/Texture/GameScene/test.png", &m_CollisionTextureIndex);

	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("Resource/Sound/damage.wav",&m_DamageSoundIndex);

	InitVertex2D();

	// TODO: ファイルを読んだりしてもっと綺麗に管理したい。
	// Lib::AnimTexture Init
	InitAnim(ANIM_WAIT, "Wait", 10);
	InitAnim(ANIM_FRONT_WALK, "FrontWalk", 7);
	InitAnim(ANIM_BACK_WALK, "BackWalk", 7);
	InitAnim(ANIM_JUMP, "Jump", 2);
	InitAnim(ANIM_SQUAT, "Squat", 3);
	InitAnim(ANIM_DAMAGE, "Damage", 4);
	InitAnim(ANIM_SQUAT_DAMAGE, "SquatDamage", 4);
	InitAnim(ANIM_GUARD, "Guard", 4);
	InitAnim(ANIM_SQUAT_GUARD, "SquatGuard", 4);
	InitAnim(ANIM_SHOT, "Shot", 4);
	InitAnim(ANIM_DOWN, "Down", 4);

	InitAnim(ANIM_LOW_PUNCH, "LowPunch", 3);
	m_SkillSpec[ANIM_LOW_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 5 ,4, 3);

	InitAnim(ANIM_HIGH_PUNCH, "HighPunch", 3);
	m_SkillSpec[ANIM_HIGH_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 10, 7, 3);
	
	InitAnim(ANIM_LOW_KICK, "LowKick", 3);
	m_SkillSpec[ANIM_LOW_KICK] = SkillSpec(&D3DXVECTOR2(0, 20), &D3DXVECTOR2(250, 10), 5, 5, 3);
	
	InitAnim(ANIM_HIGH_KICK, "HighKick", 3);
	m_SkillSpec[ANIM_HIGH_KICK] = SkillSpec(&D3DXVECTOR2(0, 20), &D3DXVECTOR2(250, 10), 10, 6, 6);

	InitAnim(ANIM_SQUAT_LOW_PUNCH, "SquatLowPunch", 3);
	m_SkillSpec[ANIM_SQUAT_LOW_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 40), &D3DXVECTOR2(180, 10), 5, 5, 3);
	
	InitAnim(ANIM_SQUAT_HIGH_PUNCH, "SquatHighPunch", 3);
	m_SkillSpec[ANIM_SQUAT_HIGH_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 40), &D3DXVECTOR2(180, 10), 10, 5, 5);
	
	InitAnim(ANIM_SQUAT_LOW_KICK, "SquatLowKick", 3);
	m_SkillSpec[ANIM_SQUAT_LOW_KICK] = SkillSpec(&D3DXVECTOR2(0, 40), &D3DXVECTOR2(180, 10), 5, 4, 6);
	
	InitAnim(ANIM_SQUAT_HIGH_KICK, "SquatHighKick", 3);
	m_SkillSpec[ANIM_SQUAT_HIGH_KICK] = SkillSpec(&D3DXVECTOR2(0, 40), &D3DXVECTOR2(180, 10), 10, 6, 6);
	// Lib::AnimTexture Init End
}

CharacterBase::~CharacterBase()
{
	m_pSquatCollisionVertex->Release();
	m_pStandCollisionVertex->Release();
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_DamageSoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_CollisionTextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Protected Functions
//----------------------------------------------------------------------------------------------------

void CharacterBase::InvertUV(D3DXVECTOR2* _uv)
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

void CharacterBase::JumpControl()
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

void CharacterBase::AttackControl()
{
	m_AnimOperation = Lib::ANIM_NORMAL;
	/* アニメーション再生が最後ならフラグを反転させてIsAttackMotionをfalseにしている */
	m_CharacterState.IsAttackMotion = !m_isAnimEnd;
	if (m_CharacterState.IsAttackMotion)
	{
		int attackAnimCount = m_pAnimTexture[m_AnimState]->GetAnimCount();

		if (m_SkillSpec[m_AnimState].FirstHitCheckCount < attackAnimCount)
		{
			m_pCollisionData->SetCollisionState(&CollisionData::CollisionState(&(m_Pos + m_SkillSpec[m_AnimState].Pos),
				&m_SkillSpec[m_AnimState].Rect, CollisionData::ATTACK, m_SkillSpec[m_AnimState].Damage));
		}
	}
	else
	{
		m_pAnimTexture[m_AnimState]->ResetAnim();
	}
}

void CharacterBase::CollisionControl()
{
	m_pCollisionData->SetCollisionState(&CollisionData::CollisionState(&m_Pos, &m_StandRectCollision, CollisionData::BODY, 0));
	SINGLETON_INSTANCE(CollisionManager).Update(m_pCollisionData->GetIndex());

	CollisionData::HIT_TYPE hitType = m_pCollisionData->GetCollisionState().HitType;
	if (hitType == CollisionData::ATTACK_HIT && !m_CharacterState.IsDamageMotion)
	{
		/* ダメージ処理 */
		DamageInit();
	}
	else if (m_CharacterState.IsDamageMotion)
	{
		/* ダメージモーション中 */
		DamageControl();
	}
	else if (hitType == CollisionData::BODY_HIT)
	{
		/* 体や壁にぶつかったとき */
		if (!m_CharacterState.IsJump)
		{
			if (m_OldPos.x == m_Pos.x)
			{
				m_CharacterState.IsRight ? m_Pos.x -= 2 : m_Pos.x += 2;
			}
			else
			{
				m_Pos.x = m_OldPos.x;
			}
		}
	}
}

void CharacterBase::CollisionDraw()
{
	if (m_CharacterState.IsSquat)
	{
		m_pSquatCollisionVertex->Draw(&D3DXVECTOR2(m_Pos.x, m_Pos.y + 40), m_UV);
	}
	else
	{
		m_pStandCollisionVertex->Draw(&m_Pos, m_UV);
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void CharacterBase::InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame)
{
	m_pAnimTexture[_animEnum] = (std::unique_ptr<Lib::AnimTexture>(new Lib::AnimTexture()));
	m_pAnimTexture[_animEnum]->LoadAnimation("Resource/Texture/GameScene/Character.anim", _animName);
	m_pAnimTexture[_animEnum]->SetAnimFrame(_setFrame);
}

void CharacterBase::InitVertex2D()
{
	m_UV[0] = D3DXVECTOR2(0, 0);
	m_UV[1] = D3DXVECTOR2(1, 0);
	m_UV[2] = D3DXVECTOR2(0, 1);
	m_UV[3] = D3DXVECTOR2(1, 1);

	m_pStandCollisionVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pStandCollisionVertex->Init(&m_StandRectCollision, m_UV);

	m_pStandCollisionVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_CollisionTextureIndex));

	m_pSquatCollisionVertex.reset(new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle()));

	m_pSquatCollisionVertex->Init(&m_SquatRectCollision, m_UV);

	m_pSquatCollisionVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).
		GetTexture(m_CollisionTextureIndex));
}

void CharacterBase::DamageInit()
{
	SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_DamageSoundIndex, Lib::DSoundManager::SOUND_PLAY);
	m_CharacterState.HP -= m_pCollisionData->GetCollisionState().ReceiveDamage;
	if (m_CharacterState.HP == 0)
	{
		m_AnimState = ANIM_DOWN;
	}
	else
	{
		m_CharacterState.IsSquat ? (m_AnimState = ANIM_SQUAT_DAMAGE) : (m_AnimState = ANIM_DAMAGE);
	}

	m_CharacterState.IsDamageMotion = true;
	m_AnimOperation = Lib::ANIM_NORMAL;
}

void CharacterBase::DamageControl()
{
	m_AnimOperation = Lib::ANIM_NORMAL;

	if (m_CharacterState.HP == 0)
	{
		m_AnimState = ANIM_DOWN;
	}
	else
	{
		m_CharacterState.IsSquat ? (m_AnimState = ANIM_SQUAT_DAMAGE) : (m_AnimState = ANIM_DAMAGE);
		if (m_isAnimEnd)
		{
			m_pAnimTexture[m_AnimState]->ResetAnim();
			m_CharacterState.IsDamageMotion = false;
		}
	}
}
