/**
 * @file   CommandManager.h
 * @brief  CommandManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

/**
 * コマンドの管理をするクラス
 */
class CommandManager
{
public:
	enum KEY
	{
		KEY_UP,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_Z,
		KEY_X,
		KEY_C,
		KEY_V,
	};

	/**
	 * コンストラクタ
	 */
	CommandManager();

	/**
	 * デストラクタ
	 */
	~CommandManager();

private:
	static const int m_KeyValidTime; //!< 次のキー入力が有効なフレーム数
	int				 m_FrameCount;
	bool			 m_isFirstKeyPush; //!< 最初のキーが押されたか?
};


#endif
