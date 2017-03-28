/**
 * @file   CharacterBase.h
 * @brief  CharacterBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H
#include <memory>
#include "../../ObjectBase/ObjecBase.h"
#include "Vertex2D.h"

/**
 * キャラクターの基底クラス
 */
class CharacterBase : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	CharacterBase(D3DXVECTOR2& _pos, D3DXVECTOR2& _rectSize, bool isRight) :
		m_Pos(_pos),
		m_RectSize(_rectSize),
		m_isRight(isRight){};

	/**
	 * デストラクタ
	 */
	~CharacterBase();

	/**
	 * 更新関数
	 */
	virtual void Update() override{};

	/**
	 * 描画関数
	 */
	virtual void Draw() override{};

protected:
	enum ANIMATION
	{
		WAIT,
		FRONT_WALK,
		BACK_WALK,
		ANIM_MAX
	};

	static const float		 m_GroundHeight;
	static const float		 m_StageWidth;

	D3DXVECTOR2				 m_Pos;
	D3DXVECTOR2				 m_RectSize;
	D3DXVECTOR2				 m_Collision;
	bool					 m_isRight;

};


#endif
