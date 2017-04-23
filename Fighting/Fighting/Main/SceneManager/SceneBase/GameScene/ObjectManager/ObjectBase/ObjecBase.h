/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <memory>
#include "Vertex2D/Vertex2D.h"

/**
 * ゲームのオブジェクトの基底クラス
 */
class ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	ObjecBase() = default;

	/**
	 * デストラクタ
	 */
	virtual ~ObjecBase() = default;

	/**
	 * 更新関数
	 */
	virtual void Update() = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() = 0;

protected:
	std::unique_ptr<Lib::Vertex2D> m_pVertex;

};


#endif
