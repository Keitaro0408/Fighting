/**
 * @file   BackGround.h
 * @brief  BackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <memory>
#include "../../ObjectBase/ObjecBase.h"
#include "Vertex2D.h"

/**
 * 背景管理クラス
 */
class BackGround : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	BackGround();

	/**
	 * デストラクタ
	 */
	~BackGround();

	/**
	 * 更新関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw()	override;

private:
	BackGround(const BackGround&);
	void operator=(const BackGround&);
	
	static const D3DXVECTOR2 m_Pos;
	static const D3DXVECTOR2 m_RectSize;
	
	std::unique_ptr<Lib::Vertex2D> m_pVertex;
	D3DXVECTOR2					   m_UV[4];
	int							   m_TextureIndex;

};


#endif
