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
	Player(const std::shared_ptr<CombatManager> &_pCombatManager);

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

	std::unique_ptr<CommandManager> m_pCommandManager;
	int							    m_TextureIndex;
	float						    m_MoveSpeed;
	Lib::ANIM_OPERATION			    m_AnimOperation; //!< アニメーションの再生設定

};


#endif
