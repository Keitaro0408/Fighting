/**
 * @file   CharacterBase.cpp
 * @brief  CharacterBaseクラスの実装
 * @author kotani
 */
#include "CharacterBase.h"
#include "../CombatManager/CombatManager.h"
#include "TextureManager.h"
#include "DX11Manager.h"
#include "Window.h"
#include "../../../CollisionManager/CollisionManager.h"

const float CharacterBase::m_GroundHeight = 550;
const float CharacterBase::m_StageWidth = 1280.f;
const float CharacterBase::m_JumpPower = 20.f;


CharacterBase::CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, const std::shared_ptr<CombatManager> &_pCombatManager, bool isRight) :
m_Pos(_pos),
m_RectSize(_rectSize),
m_pCombatManager(_pCombatManager),
m_AnimState(ANIM_WAIT),
m_isAnimEnd(false)
{
	m_CharacterState.HP = 100;
	m_CharacterState.IsRight = isRight;
	m_CharacterState.IsSquat = false;
	m_CharacterState.IsAttackMotion = false;
	m_CharacterState.IsJump = false;
	m_CharacterState.IsDamageMotion = false;

	m_StandRectCollision.x = 70;
	m_StandRectCollision.y = 200;

	m_SquatRectCollision.x = 100;
	m_SquatRectCollision.y = 100;

	SINGLETON_INSTANCE(Lib::TextureManager).
		Load("Resource/GameScene/test.png", &m_CollisionTextureIndex);

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

	InitAnim(ANIM_LOW_PUNCH, "LowPunch", 3);
	m_SkillSpec[ANIM_LOW_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 4, 3, false);

	InitAnim(ANIM_HIGH_PUNCH, "HighPunch", 3);
	m_SkillSpec[ANIM_HIGH_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 7, 3, false);
	
	InitAnim(ANIM_LOW_KICK, "LowKick", 3);
	m_SkillSpec[ANIM_LOW_KICK] = SkillSpec(&D3DXVECTOR2(0, 20), &D3DXVECTOR2(250, 10), 5, 3, false);
	
	InitAnim(ANIM_HIGH_KICK, "HighKick", 3);
	m_SkillSpec[ANIM_HIGH_KICK] = SkillSpec(&D3DXVECTOR2(0, 20), &D3DXVECTOR2(250, 10), 6, 6, false);

	InitAnim(ANIM_SQUAT_LOW_PUNCH, "SquatLowPunch", 3);
	m_SkillSpec[ANIM_SQUAT_LOW_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 6, 3, true);
	
	InitAnim(ANIM_SQUAT_LOW_KICK, "SquatLowKick", 3);
	m_SkillSpec[ANIM_SQUAT_LOW_KICK] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 4, 6, true);
	
	InitAnim(ANIM_SQUAT_HIGH_PUNCH, "SquatHighPunch", 3);
	m_SkillSpec[ANIM_SQUAT_HIGH_PUNCH] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 5, 5, true);
	
	InitAnim(ANIM_SQUAT_HIGH_KICK, "SquatHighKick", 3);
	m_SkillSpec[ANIM_SQUAT_HIGH_KICK] = SkillSpec(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(180, 10), 6, 6, true);
	// Lib::AnimTexture Init End
}

CharacterBase::~CharacterBase()
{
	SINGLETON_INSTANCE(Lib::TextureManager).
		ReleaseTexture(m_CollisionTextureIndex);

	m_pSquatCollisionVertex->Release();
	m_pStandCollisionVertex->Release();
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
	m_pAnimTexture[_animEnum]->LoadAnimation("Resource/GameScene/Character.anim", _animName);
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

void CharacterBase::DamageControl()
{
	if (m_pCollisionData->GetCollisionState().HitType == CollisionData::ATTACK_HIT &&
		!m_CharacterState.IsDamageMotion)
	{
		/* ダメージ処理 */
		m_AnimState = ANIM_DAMAGE;
		m_CharacterState.IsDamageMotion = true;
		m_AnimOperation = Lib::ANIM_NORMAL;
	}
	else if (m_CharacterState.IsDamageMotion)
	{
		m_AnimState = ANIM_DAMAGE;
		m_AnimOperation = Lib::ANIM_NORMAL;

		if (m_isAnimEnd)
		{
			m_pAnimTexture[m_AnimState]->ResetAnim();
			m_CharacterState.IsDamageMotion = false;
		}
	}
	else if (m_pCollisionData->GetCollisionState().HitType == CollisionData::BODY_HIT)
	{
		m_Pos = m_OldPos;
	}
}

