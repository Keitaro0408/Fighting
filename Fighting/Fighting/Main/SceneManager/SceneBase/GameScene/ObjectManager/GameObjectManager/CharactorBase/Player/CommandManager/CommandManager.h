/**
 * @file   CommandManager.h
 * @brief  CommandManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#define KEY_COMMAND_MAX 5

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
		KEY_LOW_PUNCH,
		KEY_HIGH_PUNCH,
		KEY_LOW_KICK,
		KEY_HIGH_KICK
	};

	/**
	 * コンストラクタ
	 */
	CommandManager();

	/**
	 * デストラクタ
	 */
	~CommandManager();

	void PushButton(KEY _key);

private:
	static const int m_KeyValidTime;   //!< 次のキー入力が有効なフレーム数

	int				 m_FrameCount;	   //!< フレーム計測用
	bool			 m_isFirstKeyPush; //!< 最初のキーが押されたか?
	int				 m_PushButtonNum;  //!< ボタン入力数
	KEY				 m_KeyCommand[KEY_COMMAND_MAX];   //!< 押されたボタンのリスト
};


#endif
