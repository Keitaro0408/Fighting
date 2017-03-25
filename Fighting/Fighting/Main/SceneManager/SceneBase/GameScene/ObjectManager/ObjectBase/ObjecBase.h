/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTBASE_H
#define OBJECTBASE_H

/**
 * ゲームのオブジェクトの基底クラス
 */
class ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	ObjecBase(){};

	/**
	 * デストラクタ
	 */
	virtual ~ObjecBase(){};

	/**
	 * 更新関数
	 */
	virtual void Update() = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() = 0;
};


#endif
