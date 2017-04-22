/**
 * @file   Player.h
 * @brief  Playerクラスのヘッダファイル
 * @author kotani
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "../../CharactorBase/CharacterBase.h"

class CommandManager;

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
	 * 使うキーのチェック
	 */
	void KeyCheck();

	/**
	 * 左のボタンの処理
	 */
	void LeftMoveControl();

	/**
	 * 右のボタンの処理
	 */
	void RightMoveControl();

	/**
	 * 上のボタンの処理
	 */
	void UpMoveControl();

	/**
	 * 下のボタンの処理
	 */
	void DownMoveControl();

	/**
	 * Zボタン処理
	 */
	void ZKeyControl();

	/**
	 * Xボタン処理
	 */
	void XKeyControl();

	/**
	 * Cボタン処理
	 */
	void CKeyControl();

	/**
	 * Vボタン処理
	 */
	void VKeyControl();

	void CommandControl();

	static const D3DXVECTOR2		m_HPBarPos;
	std::unique_ptr<CommandManager> m_pCommandManager;

	int							    m_TextureIndex;
	float						    m_MoveSpeed;

};


#endif
