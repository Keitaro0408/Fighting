/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "../../CharactorBase/CharacterBase.h"
#include "AnimTexture.h"
#include <map>

/**
 * 自分が操作するキャラクターのクラス
 */
class Player : public CharacterBase
{
public:
	/**
	 * コンストラクタ
	 */
	Player();

	/**
	 * デストラクタ
	 */
	~Player();

	/**
	 * 更新関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	typedef std::map<int ,std::unique_ptr<Lib::AnimTexture> > CharacterAnim;

	/**
	 * アニメーションの初期化
	 * @param[in] _animEnum アニメーションのenum
	 * @param[in] _animName アニメーションの名前
	 * @param[in] _setFrame 何フレームでアニメーションを進めるかの数値
	 */
	void InitAnim(ANIMATION _animEnum, LPCTSTR _animName, int _setFrame);
	
	CharacterAnim m_pAnimTexture;
	int			  m_TextureIndex;
	float		  m_MoveSpeed;
	ANIMATION	  m_PlayerAnimState;
};


#endif
