﻿/**
 * @file   CharacterBase.h
 * @brief  CharacterBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H
#include <memory>
#include <map>
#include "Vertex2D.h"
#include "AnimTexture.h"
#include "../../ObjectBase/ObjecBase.h"
#include "../../../CollisionManager/CollisionData/CollisionData.h"
#include "HPBar/HPBar.h"

class CombatManager;

/**
 * キャラクターの基底クラス
 */
class CharacterBase : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, const std::shared_ptr<CombatManager> &_pCombatManager, bool isRight);

	/**
	 * デストラクタ
	 */
	~CharacterBase();

	/**
	 * 更新関数
	 */
	virtual void Update() override{};

	/**
	 * 描画関数
	 */
	virtual void Draw() override{};

	/**
	 * 座標を取得する
	 * @return キャラクターの座標
	 */
	inline D3DXVECTOR2& GetPos()
	{
		return m_Pos;
	}

protected:
	enum ANIMATION
	{
		ANIM_WAIT,		   //!< 待機
		ANIM_FRONT_WALK,   //!< 前歩き
		ANIM_BACK_WALK,    //!< 後ろ歩き
		ANIM_DAMAGE,	   //!< ダメージ
		ANIM_SQUAT_DAMAGE, //!< しゃがみダメージ
		ANIM_JUMP,		   //!< ジャンプ
		ANIM_SQUAT,		   //!< しゃがみ
		ANIM_LOW_PUNCH,    //!< 弱パンチ
		ANIM_HIGH_PUNCH,   //!< 強パンチ
		ANIM_LOW_KICK,     //!< 弱キック
		ANIM_HIGH_KICK,	   //!< 強キック
		ANIM_SQUAT_LOW_PUNCH,  //!< しゃがみ弱パンチ
		ANIM_SQUAT_HIGH_PUNCH, //!< しゃがみ強パンチ
		ANIM_SQUAT_LOW_KICK,   //!< しゃがみ弱キック
		ANIM_SQUAT_HIGH_KICK,  //!< しゃがみ強キック
		ANIM_MAX		
	};
	typedef std::map<ANIMATION, std::unique_ptr<Lib::AnimTexture> > CharacterAnim;

	struct CharacterState
	{
		int	 HP;
		bool IsRight;
		bool IsSquat; //!< しゃがんでいるか?
		bool IsJump;  //!< ジャンプしているか?
		bool IsDamageMotion; //!< ダメージモーション中か?
		bool IsAttackMotion; //!< 攻撃中か?
	};

	struct SkillSpec
	{
		SkillSpec(){};
		SkillSpec(D3DXVECTOR2* _pos, D3DXVECTOR2* _rect,int _damage, int _firstHitCheckCount, int _hitEnableFrame)
		{
			Pos = *_pos;
			Rect = *_rect;
			Damage = _damage;
			FirstHitCheckCount = _firstHitCheckCount;
			HitEnableFrame = _hitEnableFrame;
		}
		D3DXVECTOR2 Pos;				//!< 攻撃の発生位置(プレイヤー座標からの相対)
		D3DXVECTOR2 Rect;				//!< 攻撃のサイズ
		int			Damage;				//!< ダメージ
		int			FirstHitCheckCount; //!< 判定を開始するアニメーションの番号
		int			HitEnableFrame;		//!< 何フレームの間、判定が有効かのフレーム数
	};

	/**
	 * UVの左右反転
	 * @param[in,out] _uv 反転させるUV
	 */
	void InvertUV(D3DXVECTOR2* _uv);

	/**
	 * 当たり判定の表示
	 */
	void CollisionDraw();

	/**
	 * 当たり判定処理
	 */
	void CollisionControl();

	static const float			    m_GroundHeight;
	static const float			    m_StageWidth;
	static const float			    m_JumpPower;

	std::shared_ptr<CombatManager>  m_pCombatManager;
	D3DXVECTOR2					    m_Pos;
	D3DXVECTOR2					    m_OldPos;
	D3DXVECTOR2					    m_RectSize;
	CharacterAnim				    m_pAnimTexture;
	std::map<ANIMATION, SkillSpec>  m_SkillSpec; //!< 技の性能
	ANIMATION					    m_AnimState;
	float						    m_OldHeight;
	CharacterState					m_CharacterState;
	std::unique_ptr<HPBar>			m_pHPBar;

	// 当たり判定
	std::unique_ptr<CollisionData>  m_pCollisionData;
	D3DXVECTOR2					    m_StandRectCollision; //!< 立っているときのあたり判定
	D3DXVECTOR2					    m_SquatRectCollision; //!< 座っているときのあたり判定
	std::unique_ptr<Lib::Vertex2D>  m_pStandCollisionVertex; //!< 当たり判定確認用
	std::unique_ptr<Lib::Vertex2D>  m_pSquatCollisionVertex; //!< 当たり判定確認用
	D3DXVECTOR2					    m_UV[4];
	int							    m_CollisionTextureIndex;
	Lib::ANIM_OPERATION			    m_AnimOperation; //!< アニメーションの再生設定
	bool						    m_isAnimEnd;
private:
	/**
	 * アニメーションの初期化
	 * @param[in] _animEnum アニメーションのenum
	 * @param[in] _animName アニメーションの名前
	 * @param[in] _setFrame 何フレームでアニメーションを進めるかの数値
	 */
	void InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame);
	
	/**
	 * 矩形描画のライブラリの初期化
	 */
	void InitVertex2D();

};


#endif
