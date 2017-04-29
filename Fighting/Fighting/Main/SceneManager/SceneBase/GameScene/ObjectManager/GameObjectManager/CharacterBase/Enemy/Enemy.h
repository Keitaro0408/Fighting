﻿/**
 * @file   Enemy.h
 * @brief  Enemyクラスのヘッダファイル
 * @author kotani
 */
#ifndef ENEMY_H
#define ENEMY_H
#include "../../CharacterBase/CharacterBase.h"

class Enemy : public CharacterBase
{
public:
	/**
	 * コンストラクタ
	 */
	Enemy();

	/**
	 * デストラクタ
 	 */
	~Enemy();

	/**
	 * 更新関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

private:
	static const D3DXVECTOR2 m_HPBarPos;
	int						 m_TextureIndex;
	float					 m_MoveSpeed;

};


#endif