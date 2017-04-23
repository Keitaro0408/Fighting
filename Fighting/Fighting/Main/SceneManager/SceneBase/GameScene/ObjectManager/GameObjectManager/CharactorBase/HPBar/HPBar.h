/**
 * @file   HPBar.h
 * @brief  HPBarクラスのヘッダファイル
 * @author kotani
 */
#ifndef HPBAR_H
#define HPBAR_H
#include "../../../ObjectBase/ObjecBase.h"
#include "Vertex2D/Vertex2D.h"
#include <memory>

class HPBar : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	HPBar(const D3DXVECTOR2* _pos);

	/**
	 * デストラクタ
	 */
	~HPBar();

	/**
	 * 制御関数
	 */
	void Update() override;

	void Draw() override {};

	/**
	 * 描画関数
	 */
	void Draw(int _hp);

	static const D3DXVECTOR2 m_HPBarRect;
private:
	D3DXVECTOR2 m_Pos;
	int			m_BarTextureIndex;
	int			m_BarFrameTextureIndex;
	int			m_HPBar;
	D3DXVECTOR2	m_UV[4];
	std::unique_ptr<Lib::Vertex2D> m_pBarFrameVertex;

};


#endif
