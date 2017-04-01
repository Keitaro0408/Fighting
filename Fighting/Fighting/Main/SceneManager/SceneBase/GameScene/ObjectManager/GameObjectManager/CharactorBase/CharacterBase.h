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

/**
 * キャラクターの基底クラス
 */
class CharacterBase : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, bool isRight);

	/**
	 * デストラクタ
	 */
	~CharacterBase(){};

	/**
	 * 更新関数
	 */
	virtual void Update() override{};

	/**
	 * 描画関数
	 */
	virtual void Draw() override{};

protected:
	typedef std::map<int, std::unique_ptr<Lib::AnimTexture> > CharacterAnim;
	enum ANIMATION
	{
		WAIT,
		FRONT_WALK,
		BACK_WALK,
		JUMP,
		SQUAT,
		ANIM_MAX
	};

	/**
	 * アニメーションの初期化
	 * @param[in] _animEnum アニメーションのenum
	 * @param[in] _animName アニメーションの名前
	 * @param[in] _setFrame 何フレームでアニメーションを進めるかの数値
	 */
	void InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame);

	/**
	 * UVの左右反転
	 * @param[in,out] _uv 反転させるUV
	 */
	void InvertUV(D3DXVECTOR2* _uv);


	static const float		 m_GroundHeight;
	static const float		 m_StageWidth;
	static const float		 m_JumpPower;

	int						 m_HP;
	D3DXVECTOR2				 m_Pos;
	D3DXVECTOR2				 m_RectSize;
	D3DXVECTOR2				 m_Collision;
	CharacterAnim			 m_pAnimTexture;
	ANIMATION				 m_AnimState;
	float					 m_OldHeight;
	bool					 m_isRight;
	bool					 m_isJump; //! ジャンプしているか？


};


#endif
