/**
 * @file   CharacterBase.h
 * @brief  CharacterBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H
#include <memory>
#include <map>
#include "../../ObjectBase/ObjecBase.h"
#include "Vertex2D.h"
#include "AnimTexture.h"

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
		ANIM_WAIT,		 //!< 待機
		ANIM_FRONT_WALK, //!< 前歩き
		ANIM_BACK_WALK,  //!< 後ろ歩き
		ANIM_JUMP,		 //!< ジャンプ
		ANIM_SQUAT,		 //!< しゃがみ
		ANIM_LOW_PUNCH,  //!< 弱パンチ
		ANIM_HIGH_PUNCH, //!< 強パンチ
		ANIM_LOW_KICK,   //!< 弱キック
		ANIM_HIGH_KICK,	 //!< 強キック
		ANIM_SQUAT_LOW_PUNCH,  //!< しゃがみ弱パンチ
		ANIM_SQUAT_HIGH_PUNCH, //!< しゃがみ強パンチ
		ANIM_SQUAT_LOW_KICK,   //!< しゃがみ弱キック
		ANIM_SQUAT_HIGH_KICK,  //!< しゃがみ強キック
		ANIM_MAX		
	};
	typedef std::map<ANIMATION, std::unique_ptr<Lib::AnimTexture> > CharacterAnim;

	struct CHARACTER_STATE
	{
		int	 HP;
		bool IsRight;
		bool IsSquat; //!< しゃがんでいるか?
		bool IsJump;  //!< ジャンプしているか?
		bool IsAttackMotion; //!< 攻撃中か?
	};

	struct SKILL_SPEC
	{
		SKILL_SPEC(){};
		SKILL_SPEC(int _firstHitCheckCount, int _hitEnableFrame, bool _isUnderHit)
		{
			FirstHitCheckCount = _firstHitCheckCount;
			HitEnableFrame = _hitEnableFrame;
			isUnderHit = _isUnderHit;
		}
		int FirstHitCheckCount; //!< 判定を開始するアニメーションの番号
		int HitEnableFrame;		//!< 何フレームの間、判定が有効かのフレーム数
		bool isUnderHit;		//!< しゃがんでいるとき当たるか？
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

	static const float			    m_GroundHeight;
	static const float			    m_StageWidth;
	static const float			    m_JumpPower;

	std::shared_ptr<CombatManager>  m_pCombatManager;
	D3DXVECTOR2					    m_Pos;
	D3DXVECTOR2					    m_RectSize;
	D3DXVECTOR2					    m_StandCollision; //!< 立っているときのあたり判定
	D3DXVECTOR2					    m_SquatCollision; //!< 座っているときのあたり判定
	CharacterAnim				    m_pAnimTexture;
	std::map<ANIMATION, SKILL_SPEC> m_SkillSpec; //!< 技の性能
	ANIMATION					    m_AnimState;
	float						    m_OldHeight;
	CHARACTER_STATE				    m_CharacterState;
	
	// 当たり判定確認用
	std::unique_ptr<Lib::Vertex2D> m_pStandCollisionVertex; //!< 当たり判定確認用
	std::unique_ptr<Lib::Vertex2D> m_pSquatCollisionVertex; //!< 当たり判定確認用
	D3DXVECTOR2					   m_UV[4];
	int							   m_CollisionTextureIndex;

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
