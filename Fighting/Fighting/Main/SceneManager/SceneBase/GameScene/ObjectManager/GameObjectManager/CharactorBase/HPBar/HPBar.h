/**
 * @file   HPBar.h
 * @brief  HPBarクラスのヘッダファイル
 * @author kotani
 */
#ifndef HPBAR_H
#define HPBAR_H
#include "../../../ObjectBase/ObjecBase.h"
#include "Vertex2D.h"
#include <memory>

class HPBar : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	HPBar(D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	~HPBar();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	D3DXVECTOR2 m_Pos;
	int			m_TextureIndex;
	int			m_HPBar;
	D3DXVECTOR2	m_UV[4];

};


#endif
