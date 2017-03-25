#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <D3DX10.h>

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

protected:
	D3DXVECTOR2 m_Pos;

};


#endif
