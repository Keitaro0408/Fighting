/**
 * @file   CharacterBase.cpp
 * @brief  CharacterBaseクラスの実装
 * @author kotani
 */
#include "CharacterBase.h"
#include "../CombatManager/CombatManager.h"

const float CharacterBase::m_GroundHeight = 550;
const float CharacterBase::m_StageWidth = 1280.f;
const float CharacterBase::m_JumpPower = 20.f;


CharacterBase::CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, const std::shared_ptr<CombatManager> &_pCombatManager, bool isRight) :
m_Pos(_pos),
m_RectSize(_rectSize),
m_pCombatManager(_pCombatManager),
m_AnimState(ANIM_WAIT)
{
	m_CharacterState.HP = 100;
	m_CharacterState.isRight = isRight;
	m_CharacterState.isSquat = false;
	m_CharacterState.isAttackMotion = false;
	m_CharacterState.isJump = false;

	// Lib::AnimTexture Init
	InitAnim(ANIM_WAIT, "Wait", 10);
	InitAnim(ANIM_FRONT_WALK, "FrontWalk", 7);
	InitAnim(ANIM_BACK_WALK, "BackWalk", 7);
	InitAnim(ANIM_JUMP, "Jump", 2);
	InitAnim(ANIM_SQUAT, "Squat", 3);
	InitAnim(ANIM_LOW_PUNCH, "LowPunch", 3);
	InitAnim(ANIM_HIGH_PUNCH, "HighPunch", 3);
	InitAnim(ANIM_LOW_KICK, "LowKick", 3);
	InitAnim(ANIM_HIGH_KICK, "HighKick", 3);
	InitAnim(ANIM_SQUAT_LOW_KICK, "SquatLowKick", 3);
	// Lib::AnimTexture Init End
}

//----------------------------------------------------------------------------------------------------
// Protected Functions
//----------------------------------------------------------------------------------------------------

void CharacterBase::InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame)
{
	m_pAnimTexture[_animEnum] = (std::unique_ptr<Lib::AnimTexture>(new Lib::AnimTexture()));
	m_pAnimTexture[_animEnum]->LoadAnimation("Resource/GameScene/Character.anim", _animName);
	m_pAnimTexture[_animEnum]->SetAnimFrame(_setFrame);
}

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
