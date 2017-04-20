/**
 * @file   CommandManager.h
 * @brief  CommandManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#define KEY_COMMAND_MAX 15
#include <vector>


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
		KEY_RIGHT_SLANT,
		KEY_LEFT,
		KEY_LEFT_SLANT,
		KEY_DOWN,
		KEY_LOW_PUNCH,
		KEY_HIGH_PUNCH,
		KEY_LOW_KICK,
		KEY_HIGH_KICK,
		KEY_NONE
	};

	enum COMMAND_ARTS
	{
		HADOUKEN,
		SYOURYUU
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

	void Update();

private:
	bool KeyCheck(int _arrayNum);

	static const int m_KeyValidTime;   //!< 次のキー入力が有効なフレーム数

	int				 m_FrameCount;	   //!< フレーム計測用
	bool			 m_isFirstKeyPush; //!< 最初のキーが押されたか?
	int				 m_PushButtonNum;  //!< ボタン入力数
	KEY				 m_KeyCommand[KEY_COMMAND_MAX];   //!< 押されたボタンのリスト
	std::vector<KEY> m_CheckCommandList;
	int				 m_VectorNum;
};


#endif
