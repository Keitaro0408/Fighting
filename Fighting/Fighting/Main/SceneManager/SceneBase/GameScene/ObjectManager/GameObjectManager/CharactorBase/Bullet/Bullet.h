/**
 * @file   Bullet.h
 * @brief  Bulletクラスのヘッダファイル
 * @author kotani
 */
#ifndef BULLET_H
#define BULLET_H
#include "../../../ObjectBase/ObjecBase.h"
#include "../../../../CollisionManager/CollisionData/CollisionData.h"
#include "AnimTexture.h"


/**
 * 遠距離技のオブジェクト
 */
class Bullet : public ObjecBase
{
public:
	/**
	 * コンストラクタ
	 */
	Bullet();

	/**
	 * デストラクタ
	 */
	~Bullet();

	/**
	 * 発射する前に情報を設定する
	 */
	void InitState(D3DXVECTOR2* _pos, bool _isRight);

	/**
	 * 更新関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;


private:
	/**
	 * 当たり判定処理
	 */
	void CollisionControl();

	void InvertUV(D3DXVECTOR2* _uv);


	D3DXVECTOR2						  m_Pos;
	D3DXVECTOR2					      m_RectCollision; //!< 立っているときのあたり判定
	int								  m_TextureIndex;
	bool							  m_IsRight;
	bool							  m_IsEnable; //!< 弾が存在するか
	std::unique_ptr<CollisionData>    m_pCollisionData;
	std::unique_ptr<Lib::AnimTexture> m_pAnimTexture;
};


#endif
