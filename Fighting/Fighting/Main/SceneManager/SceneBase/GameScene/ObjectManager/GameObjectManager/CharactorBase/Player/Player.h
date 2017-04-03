/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "../../CharactorBase/CharacterBase.h"

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
	/**
	 * ジャンプ処理
	 */
	void JumpControl();

	/**
	 * 左のボタンの処理
	 */
	void LeftKeyControl();

	/**
	 * 右のボタンの処理
	 */
	void RightKeyControl();

	/**
	 * 上のボタンの処理
	 */
	void UpKeyControl();

	/**
	 * 下のボタンの処理
	 */
	void DownKeyControl();

	int					m_TextureIndex;
	float				m_MoveSpeed;
	Lib::ANIM_OPERATION m_AnimOperation; //!< アニメーションの再生設定

};


#endif
